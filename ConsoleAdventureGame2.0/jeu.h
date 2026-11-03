// Role : declare les constantes, donnees et fonctions generales du jeu.
#ifndef JEU_H
#define JEU_H

#include <string>

// Dimensions de la carte et nombre fixe d ennemis.
constexpr int map_size_x = 20;
constexpr int map_size_y = 10;
constexpr int enemy_count = 5;

// Types de terrain reconnus par la carte.
enum Terrain { SOL = 0, MONTAGNE = 1, EAU = 2 };

// Donnees conservees pour chaque ennemi.
struct Enemy {
    std::string nom;
    int position_x = 0;
    int position_y = 0;
    bool vivant = false;
};

class Player;

// Variables globales : une seule definition dans jeu.cpp.
extern int map[map_size_y][map_size_x];
extern Player* joueur;
extern Enemy enemies[enemy_count];
extern int sortie_x;
extern int sortie_y;
extern bool game;

// Lit une touche et permet de quitter avec Echap.
int lireTouche();
// Traduit une touche en mouvement du joueur.
void deplacerHero(int touche);
// Elimine les ennemis situes sur une case voisine.
void attaquerEnnemis();
// Applique les degats lors d une rencontre avec un ennemi.
void verifierCollisions();
// Deplace les ennemis puis verifie les collisions.
void tourEnnemis();
// Affiche les statistiques et les commandes.
void afficherInformations();
// Affiche le message de fin apres une defaite.
void afficherFinJeu();
// Affiche le message de fin d un niveau.
void afficherVictoireNiveau();

#endif // JEU_H
