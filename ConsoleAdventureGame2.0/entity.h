#pragma once
#include <algorithm>

class Entity
{
public:
	int life = 20;
	int position_x = 0;
	int position_y = 0;

	virtual ~Entity() = default;

	void move(int input);

	void takeDamage(int damage)
	{
		life = std::max(0, life - damage);
	}

	bool isAlive() const
	{
		return life > 0;
	}
};

using entity = Entity;

