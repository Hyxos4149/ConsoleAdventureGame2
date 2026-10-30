#pragma once
#include "Equipement.h"

class Armor : public Equipement
{
public:
	int GetDefense();

private:
	int defense = 30;
};

