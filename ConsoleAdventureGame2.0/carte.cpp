#include "carte.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool chargerNiveau(const std::string& fichier, std::string& erreur) {
    std::ifstream entree(fichier.c_str());
    if (!entree) {
        erreur = "Impossible d'ouvrir le fichier de niveau : " + fichier;
        return false;
    }

    int nouvelleMap[map_size_y][map_size_x] = {};
    int hx = -1, hy = -1, sx = -1, sy = -1;
    std::vector<Enemy> nouveauxEnnemis;
    std::string ligne;
    for (int y = 0; y < map_size_y; ++y) {
        if (!std::getline(entree, ligne)) {
            erreur = "Niveau invalide dans " + fichier + " : il faut exactement 10 lignes.";
            return false;
        }
        if (!ligne.empty() && ligne.back() == '\r') ligne.pop_back();
        if (static_cast<int>(ligne.size()) != map_size_x) {
            std::ostringstream msg;
            msg << "Niveau invalide dans " << fichier << " : ligne " << (y + 1)
                << " doit contenir exactement 20 caractères.";
            erreur = msg.str();
            return false;
        }
        for (int x = 0; x < map_size_x; ++x) {
            switch (ligne[x]) {
                case '.': nouvelleMap[y][x] = SOL; break;
                case 'A': nouvelleMap[y][x] = MONTAGNE; break;
                case '~': nouvelleMap[y][x] = EAU; break;
                case 'H':
                    if (hx != -1) { erreur = "Niveau invalide : plusieurs départs H."; return false; }
                    hx = x; hy = y; nouvelleMap[y][x] = SOL; break;
                case 'E':
                    if (sx != -1) { erreur = "Niveau invalide : plusieurs sorties E."; return false; }
                    sx = x; sy = y; nouvelleMap[y][x] = SOL; break;
                case 'X': {
                    Enemy ennemi;
                    ennemi.nom = "Ennemi " + std::to_string(nouveauxEnnemis.size() + 1);
                    ennemi.position_x = x;
                    ennemi.position_y = y;
                    ennemi.vivant = true;
                    nouveauxEnnemis.push_back(ennemi);
                    nouvelleMap[y][x] = SOL;
                    break;
                }
                default:
                    erreur = "Caractère non reconnu dans " + fichier + " à la ligne " +
                             std::to_string(y + 1) + ".";
                    return false;
            }
        }
    }
    // Refuser également tout contenu non blanc après les dix rangées.
    while (std::getline(entree, ligne)) {
        if (!ligne.empty() && ligne != "\r") {
            erreur = "Niveau invalide dans " + fichier + " : contenu après la 10e ligne.";
            return false;
        }
    }
    if (hx < 0 || sx < 0) {
        erreur = "Niveau invalide dans " + fichier + " : départ H ou sortie E manquant.";
        return false;
    }
    if (static_cast<int>(nouveauxEnnemis.size()) != enemy_count) {
        erreur = "Niveau invalide dans " + fichier + " : il faut exactement 5 ennemis X.";
        return false;
    }

    for (int y = 0; y < map_size_y; ++y)
        for (int x = 0; x < map_size_x; ++x)
            map[y][x] = nouvelleMap[y][x];
    hero.position_x = hx;
    hero.position_y = hy;
    sortie_x = sx;
    sortie_y = sy;
    for (int i = 0; i < enemy_count; ++i) enemies[i] = nouveauxEnnemis[i];
    erreur.clear();
    return true;
}

void afficherCarte() {
    for (int y = 0; y < map_size_y; ++y) {
        for (int x = 0; x < map_size_x; ++x) {
            char symbole = map[y][x] == MONTAGNE ? 'A' : (map[y][x] == EAU ? '~' : '.');
            if (x == sortie_x && y == sortie_y) symbole = 'E';
            for (int i = 0; i < enemy_count; ++i)
                if (enemies[i].vivant && enemies[i].position_x == x && enemies[i].position_y == y)
                    symbole = 'X';
            if (hero.position_x == x && hero.position_y == y) symbole = 'H';
            std::cout << symbole;
        }
        std::cout << '\n';
    }
}
