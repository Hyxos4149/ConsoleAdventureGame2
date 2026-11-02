#pragma once
#include "Player.h"

class Warrior : public Player {
public:
    Warrior() : Player("Warrior", 3, 'W') {}
};