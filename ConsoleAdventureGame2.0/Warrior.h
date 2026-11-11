// Guerrier : robustesse et attaque physique.
#pragma once
#include "Player.h"
class Warrior : public virtual Player {
public:
    explicit Warrior(Vector2 depart);
    Warrior(int x, int y) : Warrior(Vector2{x, y}) {}
    char GetSymbole() const override;
};
