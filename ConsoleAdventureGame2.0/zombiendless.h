#pragma once
#include "zombie.h"

class HeadlessZombie : public Zombie
{
public:
	HeadlessZombie()
	{
		nom = "Headless Zombie";
		symbole = 'T';
		life = 30;
	}
};

using zombiendless = HeadlessZombie;

