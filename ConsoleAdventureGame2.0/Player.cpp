#include "Player.h"
#include "jeu.h"

#include <algorithm>
#include <iostream>

Player::Player(int startX, int startY) : x(startX), y(startY) {}

void Player::DisplayStats() const {
    std::cout << "Vies : " << life << '/' << maxLife << '\n';
}

void Player::TakeDamage(int value) {
    const int damage = std::max(0, value - defense - armor.GetDefense());
    SetLife(life - damage);
}

void Player::Heal(int value) {
    if (value > 0) SetLife(life + value);
}

bool Player::IsAlive() const { return life > 0; }
bool Player::CanPlay() const { return IsAlive(); }

void Player::Move(int dx, int dy) {
    const int nx = x + dx;
    const int ny = y + dy;
    if (nx < 0 || nx >= map_size_x || ny < 0 || ny >= map_size_y) return;
    // La sortie est stockee comme SOL dans map : on peut donc entrer dessus.
    if (map[ny][nx] != SOL) return;
    x = nx;
    y = ny;
}

int Player::GetLife() const { return life; }
void Player::SetLife(int value) { life = std::max(0, std::min(value, maxLife)); }
int Player::GetX() const { return x; }
int Player::GetY() const { return y; }
void Player::SetPosition(int newX, int newY) { x = newX; y = newY; }
char Player::GetSymbole() const { return '?'; }
int Player::GetAttack() const { return attack; }
