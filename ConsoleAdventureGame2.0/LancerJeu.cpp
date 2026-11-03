#include "LancerJeu.h"
#include "jeu.h"
#include "carte.h"
#include "Player.h"
#include "Warrior.h"
#include "Mage.h"
#include "WarriorMage.h"

#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace {
std::unique_ptr<Player> choisirClasse() {
    while (true) {
        std::cout << "========================\n"
                  << "   CHOIX DE TA CLASSE   \n"
                  << "========================\n\n"
                  << "1 : Warrior\n2 : Mage\n3 : WarriorMage\n\n"
                  << "Ton choix : " << std::flush;
        const int touche = _getch();
        std::cout << '\n';
        if (touche == '1') return std::make_unique<Warrior>(0, 5);
        if (touche == '2') return std::make_unique<Mage>(0, 5);
        if (touche == '3') return std::make_unique<WarriorMage>(0, 5);
        std::cout << "Choix invalide. Reessaie.\n";
    }
}

void afficherChangementNiveau(int suivant) {
    afficherVictoireNiveau();
    std::cout << "\nChangement de niveau\nPassage au niveau " << suivant
              << ". Appuie sur une touche pour continuer..." << std::flush;
    _getch();
    std::cout << '\n';
}
} // namespace

void lancerJeu() {
    const std::vector<std::string> niveaux = {"niveau1.txt", "niveau2.txt"};
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::unique_ptr<Player> proprietaire = choisirClasse();
    joueur = proprietaire.get();
    bool partieAbandonnee = false;

    for (std::size_t niveau = 0; niveau < niveaux.size(); ++niveau) {
        std::string erreur;
        if (!chargerNiveau(niveaux[niveau], erreur)) {
            std::cerr << erreur << '\n';
            game = false;
            break;
        }
        game = true;
        bool sortieAtteinte = false;

        while (game && !sortieAtteinte) {
            std::system("cls");
            afficherCarte();
            afficherInformations();
            const int touche = lireTouche();
            if (!game) {
                partieAbandonnee = true;
                break;
            }

            if (touche == ' ') {
                attaquerEnnemis();
                if (game) tourEnnemis();
            } else if (touche == 'z' || touche == 'Z' || touche == 'q' ||
                       touche == 'Q' || touche == 's' || touche == 'S' ||
                       touche == 'd' || touche == 'D') {
                deplacerHero(touche);
                if (!game) break;
                // Vérifier avant le tour ennemi : l'arrivée à la sortie termine
                // immédiatement le niveau sans donner un tour aux ennemis.
                if (joueur->GetX() == sortie_x && joueur->GetY() == sortie_y) {
                    sortieAtteinte = true;
                    break;
                }
                if (game) tourEnnemis();
            }
        }

        if (!game) break;
        if (!sortieAtteinte) break;
        if (niveau + 1 < niveaux.size()) afficherChangementNiveau(static_cast<int>(niveau + 2));
    }

    if (joueur != nullptr && !joueur->IsAlive()) afficherFinJeu();
    else if (!partieAbandonnee && game)
        std::cout << "\nVictoire finale ! Tous les niveaux sont termines.\n";
    else if (partieAbandonnee)
        std::cout << "\nTu as quitte la partie.\n";

    joueur = nullptr;
}
