// Deplacement d'une case aleatoire, conforme aux regles de l'ancien jeu.
#include "Enemy.h"
#include <cstdlib>

void Enemy::SetTurnContext(const Map* map,
                           const std::vector<std::unique_ptr<Enemy>>* ennemis) {
    map_ = map;
    ennemis_ = ennemis;
}

void Enemy::Update() {
    if (!map_ || !ennemis_) return;

    // Chaque tour, tenter une seule direction cardinale choisie au hasard.
    static constexpr Vector2 directions[4] = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };
    const Vector2 direction = directions[std::rand() % 4];
    const Vector2 cible = GetPosition() + direction;

    // IsWalkable rejette les bords, montagnes et eau; l'ancienne regle
    // interdisait aussi explicitement l'entree sur la sortie.
    if (!map_->IsWalkable(cible) || map_->IsExit(cible)) return;

    // Les autres ennemis vivants bloquent la case cible.
    for (const auto& autre : *ennemis_) {
        if (autre.get() != this && autre->IsAlive() && autre->GetPosition() == cible)
            return;
    }

    // L'ancien jeu n'empechait pas l'entree sur la case du joueur : la
    // collision est resolue ensuite par Game::VerifierCollisions().
    Move(direction);
}
