// Role : implemente les caracteristiques et les actions communes du joueur.
#include "Player.h"
#include "jeu.h"

#include <algorithm>
#include <iostream>

// Cree le joueur a sa position initiale.
Player::Player(int startX, int startY) : x(startX), y(startY) {}

// Affiche les points de vie actuels et leur maximum.
void Player::DisplayStats() const {
    std::cout << "Vies : " << life << '/' << maxLife << '\n';
}

// Calcule les degats recus et met a jour la vie.
void Player::TakeDamage(int value) {
    const int damage = std::max(0, value - defense);
    // Met a jour les points de vie dans leurs limites.
    SetLife(life - damage);
}

// Soigne le joueur si la valeur recue est positive.
void Player::Heal(int value) {
    if (value > 0) SetLife(life + value);
}

// Ces accesseurs indiquent l etat de vie et l aptitude a jouer.
// Indique si le joueur est vivant ou peut agir.
bool Player::IsAlive() const { return life > 0; }
bool Player::CanPlay() const { return IsAlive(); }

// Deplace le joueur si la case cible est dans la carte et accessible.
void Player::Move(int dx, int dy) {
    const int nx = x + dx;
    const int ny = y + dy;
    if (nx < 0 || nx >= map_size_x || ny < 0 || ny >= map_size_y) return;
    // La sortie est stockee comme SOL dans map : on peut donc entrer dessus.
    if (map[ny][nx] != SOL) return;
    x = nx;
    y = ny;
}

// Les accesseurs exposent les donnees utiles au reste du jeu.
// Accede aux points de vie et aux coordonnees du joueur.
int Player::GetLife() const { return life; }
// Limite les points de vie entre zero et le maximum.
void Player::SetLife(int value) { life = std::max(0, std::min(value, maxLife)); }
int Player::GetX() const { return x; }
int Player::GetY() const { return y; }
// Met a jour la position sans effectuer de verification de terrain.
// Met a jour la position sans verifier le terrain.
void Player::SetPosition(int newX, int newY) { x = newX; y = newY; }
// Fournit le symbole generique et l attaque de base.
char Player::GetSymbole() const { return '?'; }
int Player::GetAttack() const { return attack; }
