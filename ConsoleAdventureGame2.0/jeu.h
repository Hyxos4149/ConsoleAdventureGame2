#ifndef JEU_H
#define JEU_H

#include <string>
#include "Player.h"

constexpr int map_size_x = 20;
constexpr int map_size_y = 10;
constexpr int enemy_count = 5;

enum Terrain { SOL = 0, MONTAGNE = 1, EAU = 2 };

struct Hero {
    std::string nom;
    int position_x;
    int position_y;
    int vies;
    char direction;
};

struct Enemy {
    std::string nom;
    int position_x;
    int position_y;
    bool vivant;
};

// État partagé du jeu, défini une seule fois dans jeu.cpp.
extern int map[map_size_y][map_size_x];
extern Hero hero;
extern Enemy enemies[enemy_count];
extern int sortie_x;
extern int sortie_y;
extern bool game;

int lireTouche();
void deplacerHero(int touche);
void verifierCollisions();
void tourEnnemis();
void afficherInformations();
void afficherFinJeu();
void afficherVictoireNiveau();

extern Player* joueur;
void attaquerEnnemis();
void choisirClasse();
#endif
