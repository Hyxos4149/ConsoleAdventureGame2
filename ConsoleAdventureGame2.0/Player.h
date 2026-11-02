#pragma once
#include <string>

class Player {
protected:
    int life;
    std::string name;
    char symbole;
public:
    Player(std::string n = "Joueur", int l = 3, char s = 'H');
    virtual ~Player() {}
    void DisplayStats();
    void TakeDamage(int value);
    void Heal(int value);
    void Attack(Player& target);
    bool IsAlive();
    bool CanPlay();
    int GetLife();
    void SetLife(int value);
    char GetSymbole() { return symbole; }
};