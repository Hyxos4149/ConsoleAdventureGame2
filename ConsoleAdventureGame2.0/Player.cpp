#include <iostream>

#include "Player.h"
#include "Mage.h"

void Player::DisplayStats()
{
	std::cout << "--> Player " << '\n';
	std::cout << "Life : " << life << '\n';
	std::cout << "Attack : " << attack << '\n';
	std::cout << "Gold : " << gold << '\n';
	std::cout << '\n';
}

void Player::TakeDamage(int value)
{
	int finalAttack = value - defense - armor.GetDefense();

	if (finalAttack < 0)
		finalAttack = 0;

	SetLife(GetLife() - value);
}

void Player::Heal(int value)
{
	if (value < 0)
		value = 0;

	SetLife(GetLife() + value);
	//SetMana(GetMana() + value);
}

void Player::Attack(Player& target)
{
	int finalAttack = attack + weapon.GetAttack();

	if (finalAttack < 0)
		finalAttack = 0;

	target.TakeDamage(finalAttack);

}

bool Player::IsAlive()
{
	return life > 0;
}

bool Player::CanPlay()
{
		return IsAlive();
}

int Mage::GetMana()
{
	return 0;
}

void Mage::SetMana(int value)
{
}

int Player::GetLife()
{
	return 0;
}

void Player::SetLife(int value)
{
}

