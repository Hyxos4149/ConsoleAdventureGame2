#pragma once
#include "Player.h"

class Mage : Player
{
private:
	int life = 1;
	int maxLife = 1;

	int mana = 100;
	int attack = 50;

	Weapon weapon;

public:
	void DisplayStats();

	void TakeDamage(int value);
	void Heal(int value);
	void Attack(Player& target);


	bool IsAlive();
	bool CanPlay();

	//Getter, Setter
	int GetMana();
	void SetMana(int value);
};