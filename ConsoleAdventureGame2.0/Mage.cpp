// Sort et gestion du mana : comportement historique conserve.
#include "Mage.h"
#include <algorithm>
#include <iostream>
Mage::Mage(Vector2 depart) : Player(depart) { life_ = maxLife_ = 1; attack_ = 50; symbole_ = 'M'; }
int Mage::GetMana() const { return mana_; }
void Mage::SetMana(int valeur) { mana_ = std::max(0, valeur); }
void Mage::CastSpell() { if (mana_ >= 10) { mana_ -= 10; std::cout << "Sort lance ! Mana restant : " << mana_ << '\n'; } else std::cout << "Mana insuffisant.\n"; }
char Mage::GetSymbole() const { return 'M'; }
