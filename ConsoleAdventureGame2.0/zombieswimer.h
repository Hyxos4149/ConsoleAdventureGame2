#pragma once
#include "Enemy.h"

class ZombieSwimmer : public Enemy {
public:
	explicit ZombieSwimmer(Vector2 position = {}) : Enemy(position, 'S') {}
	void Update() override { MoveRandomly(true); }
};

using zombieswimer = ZombieSwimmer;

