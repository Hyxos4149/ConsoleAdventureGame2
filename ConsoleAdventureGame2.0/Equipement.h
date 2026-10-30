#pragma once

#include <string>

class Equipement
{
private:
	std::string name = "Default name";

public:
	void SetAttack(std::string value);
	std::string GetAttack();
};

