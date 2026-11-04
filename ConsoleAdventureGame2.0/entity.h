#pragma once
#include <algorithm>

class Entity
{
public:
	enum class tuiletype
	{
		SOL = 0,
		MONTAGNE = 1,
		EAU = 2
	};

	int life = 20;
	int position_x = 0;
	int position_y = 0;
	bool peutMarcherSurEau = false;

	virtual ~Entity() = default;

	// Déplacement et vérification du terrain.
	bool move(int deltaX, int deltaY, const int terrain[][20], tuiletype terrainAutorise);

	// Vie et dégâts.
	void takeDamage(int damage)
	{
		life = std::max(0, life - damage);
	}

	bool isAlive() const
	{
		return life > 0;
	}
};
