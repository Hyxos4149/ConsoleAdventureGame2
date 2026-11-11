// Chargement valide de la grille, sans stocker joueur ni ennemis.
#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>
namespace {
const TileInfo infos[CELL_COUNT] = {{'.', true, false}, {'A', false, false}, {'~', false, true}, {'E', true, false}};
}
const TileInfo& Map::GetTileInfo(E_CellType type) { return infos[static_cast<int>(type)]; }
bool Map::LoadFromFile(const std::string& fichier, std::string& erreur) {
    std::ifstream entree(fichier);
    if (!entree) { erreur = "Impossible d'ouvrir le niveau : " + fichier; return false; }
    std::vector<std::vector<int>> candidate(Hauteur, std::vector<int>(Largeur, SOL));
    std::string ligne;
    int nombreDepart = 0, nombreSorties = 0, nombreEnnemis = 0;
    for (int y = 0; y < Hauteur; ++y) {
        if (!std::getline(entree, ligne)) { erreur = "Niveau incomplet : lignes manquantes."; return false; }
        if (!ligne.empty() && ligne.back() == '\r') ligne.pop_back();
        if (static_cast<int>(ligne.size()) != Largeur) { erreur = "Chaque ligne doit contenir exactement 20 caracteres."; return false; }
        for (int x = 0; x < Largeur; ++x) {
            switch (ligne[x]) {
            case '.': candidate[y][x] = SOL; break;
            case 'H': ++nombreDepart; candidate[y][x] = SOL; break;
            case 'X': ++nombreEnnemis; candidate[y][x] = SOL; break;
            case 'A': candidate[y][x] = MONTAGNE; break;
            case '~': candidate[y][x] = EAU; break;
            case 'E': ++nombreSorties; candidate[y][x] = SORTIE; break;
            default: erreur = "Symbole de terrain inconnu a la ligne " + std::to_string(y + 1) + '.'; return false;
            }
        }
    }
    while (std::getline(entree, ligne)) { if (!ligne.empty() && ligne != "\r") { erreur = "Texte supplementaire apres la grille."; return false; } }
    if (nombreDepart != 1 || nombreSorties != 1 || nombreEnnemis != 5) {
        erreur = "Le niveau doit contenir exactement un H, un E et cinq X."; return false;
    }
    terrain_.swap(candidate); erreur.clear(); return true;
}
bool Map::IsWalkable(Vector2 p, bool peutNager) const {
    if (p.x < 0 || p.x >= Largeur || p.y < 0 || p.y >= Hauteur || terrain_.size() != Hauteur) return false;
    const auto type = static_cast<E_CellType>(terrain_[p.y][p.x]);
    const TileInfo& info = GetTileInfo(type);
    return info.franchissable || (info.nageable && peutNager);
}
bool Map::IsExit(Vector2 p) const { return GetCell(p) == SORTIE; }
E_CellType Map::GetCell(Vector2 p) const {
    if (p.x < 0 || p.x >= Largeur || p.y < 0 || p.y >= Hauteur || terrain_.size() != Hauteur) return MONTAGNE;
    return static_cast<E_CellType>(terrain_[p.y][p.x]);
}
void Map::Draw() const {
    for (int y = 0; y < Hauteur; ++y) { for (int x = 0; x < Largeur; ++x) std::cout << GetTileInfo(static_cast<E_CellType>(terrain_[y][x])).symbole << ' '; std::cout << '\n'; }
}
