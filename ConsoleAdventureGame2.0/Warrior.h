// Role : declare la classe Warrior, specialisee dans le combat.
#pragma once
#include "Player.h"

// Classe Warrior : specialise le joueur et definit son symbole.
class Warrior : public virtual Player {
public:
    // Cree un guerrier a la position indiquee.
    Warrior(int startX, int startY);
    // Retourne le symbole du guerrier sur la carte.
    char GetSymbole() const override;
};
