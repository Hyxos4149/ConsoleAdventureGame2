#pragma once
#include "zombie.h"

class ZombieSwimmer : public Zombie
{
public:
	ZombieSwimmer()
	{
		nom = "Zombie Swimmer";
		symbole = 'S';
		life = 25;
	}

	void swim()
	{
		move(4);
	}
};

using zombieswimer = ZombieSwimmer;

