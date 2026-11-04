#pragma once
#include "Equipement.h"

class Armor : public Equipement
{
private:
	int defense = 30;

public:
	int GetDefense();
};

