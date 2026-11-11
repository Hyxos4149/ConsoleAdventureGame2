#pragma once
#include "Enemy.h"

class HeadlessZombie : public Enemy {
public:
	explicit HeadlessZombie(Vector2 position = {}) : Enemy(position, 'T') {}
};

using zombiendless = HeadlessZombie;

