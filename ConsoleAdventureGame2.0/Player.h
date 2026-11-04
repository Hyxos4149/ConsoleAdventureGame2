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

    // Combat et soins.
    void TakeDamage(int value);
    void Heal(int value);
    void Attack(Player& target);

    // État et statistiques.
    bool IsAlive();
    bool CanPlay();
    int GetLife();
    void SetLife(int value);

    // Affichage.
    void DisplayStats();
    char GetSymbole() { return symbole; }
};