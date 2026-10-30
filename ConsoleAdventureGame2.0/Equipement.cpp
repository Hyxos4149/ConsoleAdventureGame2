#include "Equipement.h"

void Equipement::SetAttack(std::string value)
{
	name = value;
};

std::string Equipement::GetAttack()
{
	return name;
};