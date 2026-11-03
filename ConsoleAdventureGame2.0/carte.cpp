// Role : lit les fichiers de niveau et dessine la carte dans la console.
#include "carte.h"
#include "Player.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

    // Charge et valide un niveau depuis un fichier texte.
bool chargerNiveau(const std::string& fichier, std::string& erreur) {
    std::ifstream entree(fichier);
    if (!entree) {
        erreur = "Impossible d'ouvrir le fichier de niveau : " + fichier;
        return false;
    }
    if (joueur == nullptr) {
        erreur = "Le joueur doit etre cree avant de charger un niveau.";
        return false;
    }

    int nouvelleMap[map_size_y][map_size_x] = {};
    int hx = -1, hy = -1, sx = -1, sy = -1;
    std::vector<Enemy> nouveauxEnnemis;
    std::string ligne;

    for (int y = 0; y < map_size_y; ++y) {
        if (!std::getline(entree, ligne)) {
            erreur = "Niveau invalide dans " + fichier + " : lignes manquantes.";
            return false;
        }
        if (!ligne.empty() && ligne.back() == '\r') ligne.pop_back();
        if (static_cast<int>(ligne.size()) != map_size_x) {
            std::ostringstream msg;
            msg << "Niveau invalide dans " << fichier << " : la ligne " << (y + 1)
                << " doit contenir exactement " << map_size_x << " caracteres.";
            erreur = msg.str();
            return false;
        }
        for (int x = 0; x < map_size_x; ++x) {
            switch (ligne[x]) {
                case '.': nouvelleMap[y][x] = SOL; break;
                case 'A': nouvelleMap[y][x] = MONTAGNE; break;
                case '~': nouvelleMap[y][x] = EAU; break;
                case 'H':
                    if (hx != -1) { erreur = "Plusieurs departs H dans " + fichier; return false; }
                    hx = x; hy = y; nouvelleMap[y][x] = SOL; break;
                case 'E':
                    if (sx != -1) { erreur = "Plusieurs sorties E dans " + fichier; return false; }
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
                    erreur = "Caractere inconnu dans " + fichier + " a la ligne " +
                             std::to_string(y + 1) + ".";
                    return false;
            }
        }
    }
    while (std::getline(entree, ligne)) {
        if (!ligne.empty() && ligne != "\r") {
            erreur = "Contenu supplementaire apres la grille dans " + fichier;
            return false;
        }
    }
    if (hx < 0 || sx < 0) {
        erreur = "Niveau invalide dans " + fichier + " : depart H ou sortie E manquant.";
        return false;
    }
    if (static_cast<int>(nouveauxEnnemis.size()) != enemy_count) {
        erreur = "Niveau invalide dans " + fichier + " : nombre d'ennemis incorrect.";
        return false;
    }

    for (int y = 0; y < map_size_y; ++y)
        for (int x = 0; x < map_size_x; ++x)
            map[y][x] = nouvelleMap[y][x];
    joueur->SetPosition(hx, hy);
    sortie_x = sx;
    sortie_y = sy;
    for (int i = 0; i < enemy_count; ++i) enemies[i] = nouveauxEnnemis[i];
    erreur.clear();
    return true;
}

    // Affiche les symboles de toutes les cases de la carte.
void afficherCarte() {
    for (int y = 0; y < map_size_y; ++y) {
        for (int x = 0; x < map_size_x; ++x) {
            char symbole = map[y][x] == MONTAGNE ? 'A' :
                           (map[y][x] == EAU ? '~' : '.');
            if (x == sortie_x && y == sortie_y) symbole = 'E';
            for (int i = 0; i < enemy_count; ++i) {
                if (enemies[i].vivant && enemies[i].position_x == x &&
                    enemies[i].position_y == y) {
                    symbole = 'X';
                    break;
                }
            }
            if (joueur != nullptr && joueur->GetX() == x && joueur->GetY() == y)
                symbole = joueur->GetSymbole();
            std::cout << symbole << ' ';
        }
        std::cout << '\n';
    }
}
