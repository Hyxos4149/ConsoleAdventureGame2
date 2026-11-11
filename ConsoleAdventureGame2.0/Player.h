// Specialisation jouable de Entity : statistiques et actions communes aux classes.
#pragma once
#include "Entity.h"
class Player : public Entity {
protected:
    int maxLife_ = 3;
    int attack_ = 10;
    int defense_ = 0;
public:
    explicit Player(Vector2 depart);
    virtual ~Player() = default;
    void DisplayStats() const;
    void TakeDamage(int valeur) override;
    void Heal(int valeur);
    bool CanPlay() const;
    int GetAttack() const;
    void SetLife(int valeur);
};
