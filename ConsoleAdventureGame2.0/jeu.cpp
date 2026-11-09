#include "jeu.h"
#include "carte.h"
#include "Warrior.h"
#include "Mage.h"
#include "WarriorMage.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <string>

Player* joueur = nullptr;

int map[map_size_y][map_size_x] = {};
Hero hero;
Enemy enemies[enemy_count] = {};
int sortie_x = 0;
int sortie_y = 0;
bool game = true;

int lireTouche() {
    const int touche = _getch();
    if (touche == 27) {
        game = false;
        return touche;
    }
    return touche;
}

void verifierCollisions() {
    for (int i = 0; i < enemy_count; ++i) {
        if (enemies[i].vivant && enemies[i].position_x == hero.position_x &&
            enemies[i].position_y == hero.position_y) {
            enemies[i].vivant = false;
            --hero.vies;
            if (hero.vies <= 0) {
                hero.vies = 0;
                game = false;
            }
        }
    }
}

void tourEnnemis() {
    // Chaque zombie choisit son deplacement, puis le jeu verifie les obstacles.
    for (int i = 0; i < enemy_count; ++i) {
        if (!enemies[i].vivant) continue;
        enemies[i].choisirDeplacement(hero.position_x, hero.position_y);
        const int nx = enemies[i].position_x + enemies[i].deltaX;
        const int ny = enemies[i].position_y + enemies[i].deltaY;
        if (nx == sortie_x && ny == sortie_y) continue;
        bool occupee = false;
        for (int j = 0; j < enemy_count; ++j) {
            if (j != i && enemies[j].vivant && enemies[j].position_x == nx &&
                enemies[j].position_y == ny) {
                occupee = true;
                break;
            }
        }
        if (!occupee) {
            enemies[i].deplacer(enemies[i].deltaX, enemies[i].deltaY, map,
                enemies[i].terrainAutorise);
        }
    }
    verifierCollisions();
}

void afficherInformations() {
    std::cout << hero.nom << " nombres vies : " << hero.vies << "\n";
    std::cout << "Deplacement : Z/Q/S/D | echap : quitter\n";
    std::cout << "Espace = Attaquer\n";
}

void afficherFinJeu() {
    std::cout << "\nGAME OVER — partie terminee.\n";
}

void afficherVictoireNiveau() {
    std::cout << "\nNiveau termine !\n";
}

void choisirClasse() {
    system("cls");
    std::cout << "Choisis ta classe :\n";
    std::cout << "1 = Warrior (W)\n";
    std::cout << "2 = Mage (M)\n";
    std::cout << "3 = WarriorMage (H)\n";

    int choix = 0;
    while (choix < '1' || choix > '3') choix = _getch();

    if (choix == '1') joueur = new Warrior();
    else if (choix == '2') joueur = new Mage();
    else joueur = new WarriorMage();
}

void attaquerEnnemis() {
    for (int i = 0; i < enemy_count; i++) {
        if (!enemies[i].vivant) continue;
        const int dx = enemies[i].position_x - hero.position_x;
        const int dy = enemies[i].position_y - hero.position_y;
        if ((dx == 0 && (dy == 1 || dy == -1)) ||
            (dy == 0 && (dx == 1 || dx == -1))) {
            enemies[i].vivant = false;
        }
    }
}
