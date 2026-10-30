#pragma once

#include "Weapon.h"
#include "Armor.h"

class Player
{
private:
	int life = 20;
	int maxLife = 100;

	int stamina = 100;
	int attack = 10;
	int defense = 10;

	int gold = 1'000'000'000;

	Weapon weapon;
	Armor armor;

public:
	void DisplayStats();

	void TakeDamage(int value);
	void Heal(int value);
	void Attack(Player& target);


	bool IsAlive();
	bool CanPlay();

	//Getter, Setter
	int GetLife();
	void SetLife(int value);

};

