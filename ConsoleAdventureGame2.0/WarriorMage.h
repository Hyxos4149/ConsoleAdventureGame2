// Double specialisation existante : heritage virtuel partage le Player commun.
#pragma once
#include "Warrior.h"
#include "Mage.h"
class WarriorMage : public Warrior, public Mage {
public:
    explicit WarriorMage(Vector2 depart);
    WarriorMage(int x, int y) : WarriorMage(Vector2{x, y}) {}
    char GetSymbole() const override;
};
