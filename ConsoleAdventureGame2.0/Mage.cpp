#include "Mage.h"

#include <algorithm>
#include <iostream>

Mage::Mage(int startX, int startY) : Player(startX, startY) {
    life = 1;
    maxLife = 1;
    attack = 50;
}

int Mage::GetMana() const { return mana; }
void Mage::SetMana(int value) { mana = std::max(0, value); }

void Mage::CastSpell() {
    if (mana >= 10) {
        mana -= 10;
        std::cout << "Sort lance ! Mana restant : " << mana << '\n';
    }
}

char Mage::GetSymbole() const { return 'M'; }
