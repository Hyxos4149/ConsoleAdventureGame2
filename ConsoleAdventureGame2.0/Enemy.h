// Ennemi minimal : base d'Entity, avec deplacement aleatoire sur la grille.
#pragma once
#include "Entity.h"
#include "Map.h"
#include <memory>
#include <vector>

class Enemy : public Entity {
public:
    explicit Enemy(Vector2 position = {}, char symbole = 'X') : Entity(position, 1, symbole) {}
    // Le jeu fournit la carte et la liste des ennemis avant chaque tour.
    void SetTurnContext(const Map* map,
                        const std::vector<std::unique_ptr<Enemy>>* ennemis,
                        const Vector2* joueurPosition = nullptr);
    void Update() override;
protected:
    void MoveRandomly(bool peutNager);
    void MoveTowardPlayer();
private:
    const Map* map_ = nullptr;
    const std::vector<std::unique_ptr<Enemy>>* ennemis_ = nullptr;
    const Vector2* joueurPosition_ = nullptr;
};
