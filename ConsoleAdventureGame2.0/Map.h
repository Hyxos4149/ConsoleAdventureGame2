// Grille et regles de terrain uniquement : les acteurs appartiennent a Game.
#pragma once
#include "Vector2.h"
#include <string>
#include <vector>
enum E_CellType { SOL = 0, MONTAGNE = 1, EAU = 2, SORTIE = 3, CELL_COUNT = 4 };
struct TileInfo { char symbole; bool franchissable; bool nageable; };
class Map {
public:
    static constexpr int Largeur = 20, Hauteur = 10;
    bool LoadFromFile(const std::string& nomFichier, std::string& erreur);
    bool IsWalkable(Vector2 position, bool peutNager = false) const;
    bool IsExit(Vector2 position) const;
    E_CellType GetCell(Vector2 position) const;
    void Draw() const;
    static const TileInfo& GetTileInfo(E_CellType type);
private:
    std::vector<std::vector<int>> terrain_;
};
