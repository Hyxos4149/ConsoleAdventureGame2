// Boucle tour par tour et orchestration : le terrain reste dans Map.
#include "Game.h"
#include "Enemy.h"
#include "Mage.h"
#include "Player.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
namespace { constexpr Vector2 departHero{0, 5}; const char* niveaux[] = {"niveau1.txt", "niveau2.txt"}; }
Game::Game() { std::srand(static_cast<unsigned int>(std::time(nullptr))); }
Game::~Game() = default;
Game* Game::GetInstance() { static Game instance; return &instance; }
void Game::SetPlayer(std::unique_ptr<Player> joueur) { joueur_ = std::move(joueur); }
bool Game::ChargerNiveau(const std::string& fichier) {
    std::string erreur;
    if (!map_.LoadFromFile(fichier, erreur)) { std::cerr << erreur << '\n'; return false; }
    // Les X du fichier sont des points de depart et deviennent des entites, jamais du terrain.
    std::ifstream entree(fichier); std::string ligne; ennemis_.clear();
    for (int y = 0; y < Map::Hauteur && std::getline(entree, ligne); ++y)
        for (int x = 0; x < Map::Largeur && x < static_cast<int>(ligne.size()); ++x)
            if (ligne[x] == 'X') ennemis_.push_back(std::make_unique<Enemy>(Vector2{x, y}));
    if (ennemis_.size() != 5) { std::cerr << "Le niveau doit definir cinq positions X pour les ennemis.\n"; return false; }
    joueur_->SetPosition(departHero); return true;
}
void Game::Dessiner() const {
    for (int y = 0; y < Map::Hauteur; ++y) {
        for (int x = 0; x < Map::Largeur; ++x) {
            Vector2 p{x, y}; char symbole = Map::GetTileInfo(map_.GetCell(p)).symbole;
            for (const auto& ennemi : ennemis_) if (ennemi->IsAlive() && ennemi->GetPosition() == p) symbole = ennemi->GetSymbole();
            if (joueur_ && joueur_->GetPosition() == p) symbole = joueur_->GetSymbole();
            std::cout << symbole << ' ';
        } std::cout << '\n';
    }
}
void Game::Attaquer() {
    const Vector2 p = joueur_->GetPosition();
    for (auto& ennemi : ennemis_) { const Vector2 e = ennemi->GetPosition();
        if (ennemi->IsAlive() && ((e.x == p.x && (e.y == p.y-1 || e.y == p.y+1)) || (e.y == p.y && (e.x == p.x-1 || e.x == p.x+1)))) ennemi->TakeDamage(joueur_->GetAttack());
    }
}
void Game::VerifierCollisions() {
    for (auto& ennemi : ennemis_) if (ennemi->IsAlive() && ennemi->GetPosition() == joueur_->GetPosition()) { joueur_->TakeDamage(1); ennemi->TakeDamage(ennemi->GetLife()); }
    if (!joueur_->IsAlive()) partieEnCours_ = false;
}
void Game::TourJoueur(int touche) {
    Vector2 direction{};
    switch (touche) { case 'z': case 'Z': direction.y=-1; break; case 's': case 'S': direction.y=1; break; case 'q': case 'Q': direction.x=-1; break; case 'd': case 'D': direction.x=1; break;
    case ' ': Attaquer(); return;
    case 'm': case 'M': if (auto* mage = dynamic_cast<Mage*>(joueur_.get())) mage->CastSpell(); return;
    default: return; }
    const Vector2 cible = joueur_->GetPosition() + direction;
    if (map_.IsWalkable(cible)) joueur_->SetPosition(cible);
    VerifierCollisions();
}
void Game::TourEnnemis() {
    for (auto& ennemi : ennemis_) {
        if (!ennemi->IsAlive()) continue;
        ennemi->SetTurnContext(&map_, &ennemis_);
        ennemi->Update();
        VerifierCollisions(); // Collision resolue immediatement, comme avant.
        if (!joueur_->IsAlive()) break;
    }
}
void Game::Run() {
    if (!joueur_) { std::cerr << "Aucun personnage n'a ete choisi.\n"; return; }
    partieEnCours_ = true; abandon_ = false;
    for (niveauCourant_ = 0; niveauCourant_ < 2 && partieEnCours_; ++niveauCourant_) {
        if (!ChargerNiveau(niveaux[niveauCourant_])) { partieEnCours_ = false; break; }
        bool sortieAtteinte = false;
        while (partieEnCours_ && !sortieAtteinte) {
            std::system("cls"); Dessiner(); joueur_->DisplayStats();
            std::cout << "Z/Q/S/D : deplacement | Espace : attaque | M : sort Mage | Echap : quitter\n";
            const int touche = _getch();
            if (touche == 27) { abandon_ = true; partieEnCours_ = false; break; }
            const bool deplacement = touche == 'z' || touche == 'Z' || touche == 'q' || touche == 'Q' ||
                                     touche == 's' || touche == 'S' || touche == 'd' || touche == 'D';
            const bool sortOuMagie = touche == ' ' ||
                                     ((touche == 'm' || touche == 'M') && dynamic_cast<Mage*>(joueur_.get()));
            if (!deplacement && !sortOuMagie) continue;
            TourJoueur(touche);
            if (!partieEnCours_) break;
            sortieAtteinte = map_.IsExit(joueur_->GetPosition());
            if (!sortieAtteinte) TourEnnemis();
        }
        if (sortieAtteinte && niveauCourant_ == 0) { std::cout << "Niveau termine ! Passage au niveau 2. Appuie sur une touche...\n"; _getch(); }
    }
    if (joueur_ && !joueur_->IsAlive()) std::cout << "\nGAME OVER - partie terminee.\n";
    else if (abandon_) std::cout << "\nTu as quitte la partie.\n";
    else if (partieEnCours_) std::cout << "\nVictoire finale ! Tous les niveaux sont termines.\n";
}
