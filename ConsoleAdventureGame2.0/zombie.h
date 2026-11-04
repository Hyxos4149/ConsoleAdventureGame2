#pragma once
#include "entity.h"
#include <string>

enum class Deplacement
{
	VersJoueur,
	Aleatoire
};

class Zombie : public Entity
{
public:
	// Identité et état.
	std::string nom = "Zombie";
	char symbole = 'Z';
	bool vivant = true;

	// Déplacement.
	int deltaX = 0;
	int deltaY = 0;
	Deplacement typeDeplacement = Deplacement::VersJoueur;
	tuiletype terrainAutorise = tuiletype::SOL;

	void choisirDeplacement(int cibleX, int cibleY);
};

