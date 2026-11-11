#pragma once
#include "Enemy.h"

class Zombie : public Enemy {
public:
	explicit Zombie(Vector2 position = {}) : Enemy(position, 'Z') {}
	void Update() override { MoveTowardPlayer(); }
};

using zombie = Zombie;

