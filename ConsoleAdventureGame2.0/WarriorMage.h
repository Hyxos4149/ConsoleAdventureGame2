#pragma once
#include "Warrior.h"
#include "Mage.h"

class WarriorMage : public Player {
protected:
    int mana;
public:
    WarriorMage() : Player("WarriorMage", 3, 'H'), mana(10) {}
};