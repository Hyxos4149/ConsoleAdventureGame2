// Ennemi minimal : base d'Entity, avec deplacement aleatoire sur la grille.
#pragma once
#include "Entity.h"
#include "Map.h"
#include <memory>
#include <vector>

class Enemy : public Entity {
public:
    explicit Enemy(Vector2 position = {}) : Entity(position, 1, 'X') {}
    // Le jeu fournit la carte et la liste des ennemis avant chaque tour.
    void SetTurnContext(const Map* map,
                        const std::vector<std::unique_ptr<Enemy>>* ennemis);
    void Update() override;
private:
    const Map* map_ = nullptr;
    const std::vector<std::unique_ptr<Enemy>>* ennemis_ = nullptr;
};
