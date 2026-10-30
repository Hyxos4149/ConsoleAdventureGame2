#pragma once

#include "Equipement.h"

class Weapon : public Equipement
{
public: 
	int GetAttack();

private: 
	int attack = 30;

};

