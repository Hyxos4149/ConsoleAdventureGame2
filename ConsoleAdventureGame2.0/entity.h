#pragma once
class entity
{
public:
	int life = 20;
	int position_x = 0;
	int position_y = 0;

	void move(int input) {
		if (input == 1) {
			position_y--;
		}
		else if (input == 2) {
			position_y++;
		}
		else if (input == 3) {
			position_x--;
		}
		else if (input == 4) {
			position_x++;
		}
	}
};

