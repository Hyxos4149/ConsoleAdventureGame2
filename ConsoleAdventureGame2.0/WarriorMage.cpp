// Le personnage mixte reprend les statistiques resistantes du guerrier.
#include "WarriorMage.h"
WarriorMage::WarriorMage(Vector2 depart) : Player(depart), Warrior(depart), Mage(depart) { life_ = maxLife_ = 3; attack_ = 50; symbole_ = 'H'; }
char WarriorMage::GetSymbole() const { return 'H'; }
