// Implementations partagees : elles ne dependent pas du type de terrain.
#include "Entity.h"
#include <algorithm>
Entity::Entity(Vector2 position, int vie, char symbole) : position_(position), life_(std::max(0, vie)), symbole_(symbole) {}
char Entity::GetSymbole() const { return symbole_; }
void Entity::Update() {}
void Entity::Move(Vector2 direction) { position_ += direction; }
void Entity::TakeDamage(int degats) { life_ = std::max(0, life_ - std::max(0, degats)); }
bool Entity::IsAlive() const { return life_ > 0; }
Vector2 Entity::GetPosition() const { return position_; }
void Entity::SetPosition(Vector2 position) { position_ = position; }
int Entity::GetLife() const { return life_; }
