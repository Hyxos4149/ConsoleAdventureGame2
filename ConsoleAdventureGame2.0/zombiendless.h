#pragma once
#include "zombie.h"

class HeadlessZombie : public Zombie
{
public:
	HeadlessZombie()
	{
		nom = "Headless Zombie";
		life = 30;
		symbole = 'T';
		typeDeplacement = Deplacement::Aleatoire;
	}
};



