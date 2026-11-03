#pragma once
#include "Player.h"

class Mage : public virtual Player {
private:
    int mana = 100;

public:
    Mage(int startX, int startY);
    int GetMana() const;
    void SetMana(int value);
    void CastSpell();
    char GetSymbole() const override;
};
