#pragma once
#include "entity.h"
#include <string>

class Zombie : public Entity
{
public:
	std::string nom = "Zombie";
	char symbole = 'Z';
	bool vivant = true;
};

