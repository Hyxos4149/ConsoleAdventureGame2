#include "entity.h"

bool Entity::move(int deltaX, int deltaY, const int terrain[][20], tuiletype terrainAutorise)
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
