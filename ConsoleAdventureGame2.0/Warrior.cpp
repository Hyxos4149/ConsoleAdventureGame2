// Role : implemente le constructeur et le symbole du guerrier.
#include "Warrior.h"

// Initialise les caracteristiques propres au guerrier.
Warrior::Warrior(int startX, int startY) : Player(startX, startY) {
    life = 3;
    maxLife = 3;
    attack = 50;
}

// Retourne le caractere du guerrier sur la carte.
char Warrior::GetSymbole() const { return 'W'; }
