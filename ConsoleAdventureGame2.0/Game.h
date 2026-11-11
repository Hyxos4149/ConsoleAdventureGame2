// Singleton de la partie : possede la carte, le joueur, les ennemis et leur cycle.
#pragma once
#include "Map.h"
#include <memory>
#include <string>
#include <vector>
class Player;
class Enemy;
class Game {
public:
    static Game* GetInstance();
    ~Game(); // Defini dans Game.cpp, ou les types Player et Enemy sont complets.
    void Run();
    void SetPlayer(std::unique_ptr<Player> joueur);
private:
    Game();
    bool ChargerNiveau(const std::string& fichier);
    void Dessiner() const;
    void TourJoueur(int touche);
    void TourEnnemis();
    void Attaquer();
    void VerifierCollisions();
    Map map_;
    std::unique_ptr<Player> joueur_;
    std::vector<std::unique_ptr<Enemy>> ennemis_;
    int niveauCourant_ = 0;
    bool partieEnCours_ = true;
    bool abandon_ = false;
};
