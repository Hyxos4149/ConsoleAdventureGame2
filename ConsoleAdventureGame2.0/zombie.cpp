#include "zombie.h"
#include <cstdlib>

void Zombie::choisirDeplacement(int cibleX, int cibleY)
{
	deltaX = 0;
	deltaY = 0;

	if (typeDeplacement == Deplacement::Aleatoire) {
		const int direction = std::rand() % 4;
		if (direction == 0) deltaY = -1;
		else if (direction == 1) deltaY = 1;
		else if (direction == 2) deltaX = -1;
		else deltaX = 1;
		return;
	}

	const int distanceX = cibleX - position_x;
	const int distanceY = cibleY - position_y;
	if (distanceX > 0) {
		deltaX = 1;
	}
	else if (distanceX < 0) {
		deltaX = -1;
	}
	else {
		deltaX = 0;
	}
	if (distanceY > 0) {
		deltaY = 1;
	}
	else if (distanceY < 0) {
		deltaY = -1;
	}
	else {
		deltaY = 0;
	}
}
