#include "Player.h"
#include <iostream>

Player::Player(std::string n, int l, char s) : life(l), name(n), symbole(s) {}

void Player::DisplayStats() {
    std::cout << name << " - Vies : " << life << '\n';
}
void Player::TakeDamage(int value) {
    life -= value;
    if (life < 0) life = 0;
}
void Player::Heal(int value) { life += value; }
void Player::Attack(Player& target) { target.TakeDamage(1); }
bool Player::IsAlive() { return life > 0; }
bool Player::CanPlay() { return IsAlive(); }
int Player::GetLife() { return life; }
void Player::SetLife(int value) { life = value; }