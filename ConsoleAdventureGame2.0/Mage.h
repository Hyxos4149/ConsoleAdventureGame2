// Mage : fragile mais puissant, avec une reserve de mana.
#pragma once
#include "Player.h"
class Mage : public virtual Player {
private:
    int mana_ = 100;
public:
    explicit Mage(Vector2 depart);
    Mage(int x, int y) : Mage(Vector2{x, y}) {}
    int GetMana() const;
    void SetMana(int valeur);
    void CastSpell();
    char GetSymbole() const override;
};
