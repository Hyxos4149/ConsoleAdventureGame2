#pragma once
#include "Player.h"

class Mage : public Player {
protected:
    int mana;
public:
    Mage() : Player("Mage", 1, 'M'), mana(10) {}
    int GetMana();
    void SetMana(int value);
};