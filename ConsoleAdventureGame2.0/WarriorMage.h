#pragma once
#include "Warrior.h"
#include "Mage.h"

class WarriorMage : public Warrior, public Mage {
public:
    WarriorMage(int startX, int startY);
    char GetSymbole() const override;
};
