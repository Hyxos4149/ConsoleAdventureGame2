#include "jeu.h"
#include "carte.h"

#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <string>

int map[map_size_y][map_size_x] = {};
Hero hero = {"Héros", 0, 5, 3, 's'};
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

void deplacerHero(int touche) {
    int dx = 0, dy = 0;
    switch (touche) {
        case 'z': case 'Z': dy = -1; hero.direction = 'z'; break;
        case 's': case 'S': dy = 1;  hero.direction = 's'; break;
        case 'q': case 'Q': dx = -1; hero.direction = 'q'; break;
        case 'd': case 'D': dx = 1;  hero.direction = 'd'; break;
        default: return;
    }

    const int nx = hero.position_x + dx;
    const int ny = hero.position_y + dy;
    if (nx < 0 || nx >= map_size_x || ny < 0 || ny >= map_size_y) return;
    if (map[ny][nx] != SOL) return;
    hero.position_x = nx;
    hero.position_y = ny;
    verifierCollisions();
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
    // Chaque ennemi vivant tente un déplacement aléatoire vers une case libre.
    static const int dx[4] = {0, 0, -1, 1};
    static const int dy[4] = {-1, 1, 0, 0};
    for (int i = 0; i < enemy_count; ++i) {
        if (!enemies[i].vivant) continue;
        const int direction = std::rand() % 4;
        const int nx = enemies[i].position_x + dx[direction];
        const int ny = enemies[i].position_y + dy[direction];
        if (nx < 0 || nx >= map_size_x || ny < 0 || ny >= map_size_y) continue;
        if (map[ny][nx] != SOL || (nx == sortie_x && ny == sortie_y)) continue;
        bool occupee = false;
        for (int j = 0; j < enemy_count; ++j) {
            if (j != i && enemies[j].vivant && enemies[j].position_x == nx &&
                enemies[j].position_y == ny) {
                occupee = true;
                break;
            }
        }
        if (!occupee) {
            enemies[i].position_x = nx;
            enemies[i].position_y = ny;
        }
    }
    verifierCollisions();
}

void afficherInformations() {
    std::cout << hero.nom << " — vies : " << hero.vies << "\n";
    std::cout << "Deplacement : Z/Q/S/D | Échap : quitter\n";
}

void afficherFinJeu() {
    std::cout << "\nGAME OVER — partie terminee.\n";
}

void afficherVictoireNiveau() {
    std::cout << "\nNiveau termine !\n";
}
