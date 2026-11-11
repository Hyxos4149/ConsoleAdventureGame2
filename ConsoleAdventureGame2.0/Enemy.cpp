// Deplacement d'une case aleatoire, conforme aux regles de l'ancien jeu.
#include "Enemy.h"
#include <cstdlib>
#include <queue>

void Enemy::SetTurnContext(const Map* map,
                            const std::vector<std::unique_ptr<Enemy>>* ennemis,
                            const Vector2* joueurPosition) {
    map_ = map;
    ennemis_ = ennemis;
    joueurPosition_ = joueurPosition;
}

void Enemy::Update() {
    MoveRandomly(false);
}

void Enemy::MoveRandomly(bool peutNager) {
    if (!map_ || !ennemis_) return;

    // Chaque tour, tenter une seule direction cardinale choisie au hasard.
    static constexpr Vector2 directions[4] = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };
    const Vector2 direction = directions[std::rand() % 4];
    const Vector2 cible = GetPosition() + direction;

    // IsWalkable rejette les bords et les montagnes; l'eau est autorisee
    // uniquement pour les ennemis nageurs.
    if (!map_->IsWalkable(cible, peutNager) || map_->IsExit(cible)) return;

    // Les autres ennemis vivants bloquent la case cible.
    for (const auto& autre : *ennemis_) {
        if (autre.get() != this && autre->IsAlive() && autre->GetPosition() == cible)
            return;
    }

    // L'ancien jeu n'empechait pas l'entree sur la case du joueur : la
    // collision est resolue ensuite par Game::VerifierCollisions().
    Move(direction);
}

void Enemy::MoveTowardPlayer() {
    if (!map_ || !ennemis_ || !joueurPosition_) return;

    const Vector2 depart = GetPosition();
    const Vector2 arrivee = *joueurPosition_;
    if (depart == arrivee) return;

    static constexpr Vector2 directions[4] = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };
    bool visitee[Map::Hauteur][Map::Largeur]{};
    Vector2 precedent[Map::Hauteur][Map::Largeur]{};
    std::queue<Vector2> aVisiter;
    aVisiter.push(depart);
    visitee[depart.y][depart.x] = true;

    while (!aVisiter.empty()) {
        const Vector2 actuelle = aVisiter.front();
        aVisiter.pop();
        if (actuelle == arrivee) break;

        for (const Vector2 direction : directions) {
            const Vector2 suivante = actuelle + direction;
            if (suivante.x < 0 || suivante.x >= Map::Largeur ||
                suivante.y < 0 || suivante.y >= Map::Hauteur ||
                visitee[suivante.y][suivante.x] ||
                !map_->IsWalkable(suivante) || map_->IsExit(suivante))
                continue;

            bool occupee = false;
            for (const auto& autre : *ennemis_) {
                if (autre.get() != this && autre->IsAlive() &&
                    autre->GetPosition() == suivante) {
                    occupee = true;
                    break;
                }
            }
            if (occupee && suivante != arrivee) continue;

            visitee[suivante.y][suivante.x] = true;
            precedent[suivante.y][suivante.x] = actuelle;
            aVisiter.push(suivante);
        }
    }

    if (!visitee[arrivee.y][arrivee.x]) return;

    Vector2 prochaine = arrivee;
    while (precedent[prochaine.y][prochaine.x] != depart)
        prochaine = precedent[prochaine.y][prochaine.x];
    Move(prochaine + Vector2{-depart.x, -depart.y});
}
