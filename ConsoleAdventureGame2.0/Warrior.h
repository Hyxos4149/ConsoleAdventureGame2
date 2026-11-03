#pragma once
#include "Player.h"

class Warrior : public virtual Player {
public:
    Warrior(int startX, int startY);
    char GetSymbole() const override;
};
