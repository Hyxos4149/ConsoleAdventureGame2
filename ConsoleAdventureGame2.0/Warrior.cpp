#include "Warrior.h"

Warrior::Warrior(int startX, int startY) : Player(startX, startY) {
    life = 3;
    maxLife = 3;
    attack = 50;
}

char Warrior::GetSymbole() const { return 'W'; }
