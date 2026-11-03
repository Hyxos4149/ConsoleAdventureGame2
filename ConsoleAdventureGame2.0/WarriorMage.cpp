#include "WarriorMage.h"

WarriorMage::WarriorMage(int startX, int startY)
    : Player(startX, startY), Warrior(startX, startY), Mage(startX, startY) {
    life = 3;
    maxLife = 3;
    attack = 50;
}

char WarriorMage::GetSymbole() const { return 'H'; }
