#pragma once

#include "Weapon.h"
#include "Armor.h"

class Player {
protected:
    int life = 3;
    int maxLife = 3;
    int attack = 10;
    int defense = 0;
    int x = 0;
    int y = 0;
    Weapon weapon;
    Armor armor;

public:
    Player(int startX, int startY);
    virtual ~Player() = default;

    void DisplayStats() const;
    virtual void TakeDamage(int value);
    void Heal(int value);
    bool IsAlive() const;
    bool CanPlay() const;
    void Move(int dx, int dy);

    int GetLife() const;
    void SetLife(int value);
    int GetX() const;
    int GetY() const;
    void SetPosition(int newX, int newY);
    virtual char GetSymbole() const;
    virtual int GetAttack() const;
};
