#include "entity.h"

void Entity::move(int input)
{
	if (input == 1) {
		--position_y;
	}
	else if (input == 2) {
		++position_y;
	}
	else if (input == 3) {
		--position_x;
	}
	else if (input == 4) {
		++position_x;
	}
}
