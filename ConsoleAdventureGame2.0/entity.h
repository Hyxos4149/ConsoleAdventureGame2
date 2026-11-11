
// Classe mere commune aux personnages : position, vie, deplacement et representation.
#pragma once
#include "Vector2.h"

class Entity {
protected:
    Vector2 position_;
    int life_ = 1;
    char symbole_ = '?';
public:
    explicit Entity(Vector2 position = {}, int vie = 1, char symbole = '?');
    virtual ~Entity() = default;
    virtual char GetSymbole() const;
    virtual void Update(); // Un tour vide par defaut, remplacable par les ennemis.
    virtual void Move(Vector2 direction);
    virtual void TakeDamage(int degats);
    bool IsAlive() const;
    Vector2 GetPosition() const;
    void SetPosition(Vector2 position);
    int GetLife() const;
};
