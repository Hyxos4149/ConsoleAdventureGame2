// Role : implemente le personnage qui combine les deux classes.
#include "WarriorMage.h"

// Initialise les bases partagees et les caracteristiques combinees.
WarriorMage::WarriorMage(int startX, int startY)
    // Cree le joueur a sa position initiale.
    : Player(startX, startY), Warrior(startX, startY), Mage(startX, startY) {
    life = 3;
    maxLife = 3;
    attack = 50;
}

// Retourne le caractere du personnage combine sur la carte.
char WarriorMage::GetSymbole() const { return 'H'; }
