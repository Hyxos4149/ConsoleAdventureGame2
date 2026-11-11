// Logique de combat commune aux guerriers, mages et personnage combine.
#include "Player.h"
#include <algorithm>
#include <iostream>
Player::Player(Vector2 depart) : Entity(depart, 3, '?') {}
void Player::DisplayStats() const { std::cout << "Vies : " << life_ << '/' << maxLife_ << '\n'; }
void Player::TakeDamage(int valeur) { SetLife(life_ - std::max(0, valeur - defense_)); }
void Player::Heal(int valeur) { if (valeur > 0) SetLife(life_ + valeur); }
bool Player::CanPlay() const { return IsAlive(); }
int Player::GetAttack() const { return attack_; }
void Player::SetLife(int valeur) { life_ = std::max(0, std::min(valeur, maxLife_)); }
