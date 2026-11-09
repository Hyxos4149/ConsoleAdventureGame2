#pragma once
#include <algorithm>
#include <string>

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
	char symbole = 'H';

	virtual ~Entity() = default;

	// Déplacement commun et vérification du terrain pour toutes les entités.
	bool deplacer(int deltaX, int deltaY, const int terrain[][20], tuiletype terrainAutorise);

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

class Hero : public Entity
{
public:
	std::string nom = "Heros";
	int vies = 3;
	char direction = 's';

	// Traduit la touche en déplacement et applique le déplacement valide.
	bool deplacer(int touche, const int terrain[][20]);
};
