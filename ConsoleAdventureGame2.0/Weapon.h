#pragma once

#include "Equipement.h"

class Weapon : public Equipement
{
private: 
	int attack = 30;

public:
	int GetAttack();
};

