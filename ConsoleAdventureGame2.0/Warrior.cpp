// Reglages de base du guerrier.
#include "Warrior.h"
Warrior::Warrior(Vector2 depart) : Player(depart) { life_ = maxLife_ = 3; attack_ = 50; symbole_ = 'W'; }
char Warrior::GetSymbole() const { return 'W'; }
