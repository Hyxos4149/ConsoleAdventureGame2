#ifndef JEU_H
#define JEU_H

#include <string>

constexpr int map_size_x = 20;
constexpr int map_size_y = 10;
constexpr int enemy_count = 5;

enum Terrain { SOL = 0, MONTAGNE = 1, EAU = 2 };

struct Enemy {
    std::string nom;
    int position_x = 0;
    int position_y = 0;
    bool vivant = false;
};

class Player;

// Variables globales : une seule définition dans jeu.cpp.
extern int map[map_size_y][map_size_x];
extern Player* joueur;
extern Enemy enemies[enemy_count];
extern int sortie_x;
extern int sortie_y;
extern bool game;

int lireTouche();
void deplacerHero(int touche);
void attaquerEnnemis();
void verifierCollisions();
void tourEnnemis();
void afficherInformations();
void afficherFinJeu();
void afficherVictoireNiveau();

#endif // JEU_H
