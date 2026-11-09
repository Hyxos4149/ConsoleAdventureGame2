#include "entity.h"

bool Entity::deplacer(int deltaX, int deltaY, const int terrain[][20], tuiletype terrainAutorise)
{
	const int nPositionX = position_x + deltaX;
	const int nPositionY = position_y + deltaY;

	if (nPositionX < 0 || nPositionX >= 20 ||
		nPositionY < 0 || nPositionY >= 10) return false;

	const int tuile = terrain[nPositionY][nPositionX];
	if (tuile != static_cast<int>(terrainAutorise) &&
		(!peutMarcherSurEau || tuile != static_cast<int>(tuiletype::EAU))) return false;

	position_x = nPositionX;
	position_y = nPositionY;
	return true;
}

bool Hero::deplacer(int touche, const int terrain[][20])
{
	int deltaX = 0;
	int deltaY = 0;

	switch (touche) {
	case 'z': case 'Z': deltaY = -1; direction = 'z'; break;
	case 's': case 'S': deltaY = 1; direction = 's'; break;
	case 'q': case 'Q': deltaX = -1; direction = 'q'; break;
	case 'd': case 'D': deltaX = 1; direction = 'd'; break;
	default: return false;
	}

	return Entity::deplacer(deltaX, deltaY, terrain, tuiletype::SOL);
}
