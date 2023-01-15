#include "headers/enemy.h"
#include <raylib.h>

Enemy::Enemy(std::string name, int health, int energy, int speed,
             std::vector<Attack> attacks) {
  this->name = name;
  this->maxHealth = health;
  this->currentHealth = health;
  this->maxEnergy = energy;
  this->currentEnergy = energy;
  this->speed = speed;
  this->attacks = attacks;
  this->canBeDeleted = false;
}

void Enemy::takeDamage(int dmg) { this->currentHealth -= dmg; }

bool Enemy::isDead() { return this->currentHealth < 1; }

void Enemy::draw(Rectangle pos) {
  if (this->isDead()) {
    // play death anim then mark canBeDeleted
    DrawRectangleRec(pos, RED);
  } else {
    DrawRectangleRec(pos, YELLOW);
  }
}

void Enemy::update() { GetFrameTime(); }
