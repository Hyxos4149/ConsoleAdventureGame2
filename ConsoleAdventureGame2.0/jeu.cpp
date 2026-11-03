#include "jeu.h"
#include "Player.h"

#include <conio.h>
#include <cstdlib>
#include <iostream>

int map[map_size_y][map_size_x] = {};
Player* joueur = nullptr;
Enemy enemies[enemy_count] = {};
int sortie_x = 0;
int sortie_y = 0;
bool game = true;

int lireTouche() {
    const int touche = _getch();
    if (touche == 27) game = false;
    // Espace (32) est renvoyee telle quelle et traitee comme une action.
    return touche;
}

void deplacerHero(int touche) {
    if (joueur == nullptr) return;
    int dx = 0;
    int dy = 0;
    switch (touche) {
        case 'z': case 'Z': dy = -1; break;
        case 's': case 'S': dy = 1; break;
        case 'q': case 'Q': dx = -1; break;
        case 'd': case 'D': dx = 1; break;
        default: return;
    }
    joueur->Move(dx, dy);
    verifierCollisions();
}

void attaquerEnnemis() {
    if (joueur == nullptr) return;
    static constexpr int dx[4] = {0, 0, -1, 1};
    static constexpr int dy[4] = {-1, 1, 0, 0};
    for (int i = 0; i < enemy_count; ++i) {
        if (!enemies[i].vivant) continue;
        const int ex = enemies[i].position_x;
        const int ey = enemies[i].position_y;
        for (int direction = 0; direction < 4; ++direction) {
            if (ex == joueur->GetX() + dx[direction] &&
                ey == joueur->GetY() + dy[direction]) {
                enemies[i].vivant = false;
                break;
            }
        }
    }
}

void verifierCollisions() {
    if (joueur == nullptr) return;
    for (int i = 0; i < enemy_count; ++i) {
        if (enemies[i].vivant &&
            enemies[i].position_x == joueur->GetX() &&
            enemies[i].position_y == joueur->GetY()) {
            enemies[i].vivant = false;
            joueur->TakeDamage(1);
            if (!joueur->IsAlive()) {
                game = false;
                return;
            }
        }
    }
}

void tourEnnemis() {
    if (joueur == nullptr || !joueur->IsAlive()) return;
    static constexpr int dx[4] = {0, 0, -1, 1};
    static constexpr int dy[4] = {-1, 1, 0, 0};
    for (int i = 0; i < enemy_count; ++i) {
        if (!enemies[i].vivant) continue;
        const int direction = std::rand() % 4;
        const int nx = enemies[i].position_x + dx[direction];
        const int ny = enemies[i].position_y + dy[direction];
        if (nx < 0 || nx >= map_size_x || ny < 0 || ny >= map_size_y) continue;
        if (map[ny][nx] != SOL || (nx == sortie_x && ny == sortie_y)) continue;
        bool occupee = false;
        for (int j = 0; j < enemy_count; ++j) {
            if (j != i && enemies[j].vivant &&
                enemies[j].position_x == nx && enemies[j].position_y == ny) {
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
    if (joueur != nullptr) joueur->DisplayStats();
    std::cout << "Deplacement : Z/Q/S/D | Espace = Attaquer | Echap = Quitter\n";
}

void afficherFinJeu() {
    std::cout << "\nGAME OVER : partie terminee.\n";
}

void afficherVictoireNiveau() {
    std::cout << "\nNiveau termine !\n";
}
