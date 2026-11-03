// Role : declare le personnage qui combine Warrior et Mage.
#pragma once
#include "Warrior.h"
#include "Mage.h"

// Classe combinee : herite des deux classes specialisees.
class WarriorMage : public Warrior, public Mage {
public:
    // Cree le personnage combine a la position indiquee.
    WarriorMage(int startX, int startY);
    // Retourne le symbole du personnage combine.
    char GetSymbole() const override;
};
