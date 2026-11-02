#pragma once
#include "Player.h"
class Warrior : Player
{
private:
	int life = 3;
	int maxLife = 3;

	int Stamina = 100;
	int attack = 50;

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

