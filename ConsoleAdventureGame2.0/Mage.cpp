// Role : implemente les statistiques et les capacites du mage.
#include "Mage.h"

#include <algorithm>
#include <iostream>

// Initialise les caracteristiques propres au mage.
Mage::Mage(int startX, int startY) : Player(startX, startY) {
    life = 1;
    maxLife = 1;
    attack = 50;
}

// Lit ou modifie la reserve de mana.
int Mage::GetMana() const { return mana; }
// Met a jour le mana sans valeur negative.
void Mage::SetMana(int value) { mana = std::max(0, value); }

// Consomme dix points de mana et signale le lancement du sort.
void Mage::CastSpell() {
    if (mana >= 10) {
        mana -= 10;
        std::cout << "Sort lance ! Mana restant : " << mana << '\n';
    }
}

// Retourne le caractere du mage sur la carte.
char Mage::GetSymbole() const { return 'M'; }
