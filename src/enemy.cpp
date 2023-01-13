#include "headers/enemy.h"
#include <raylib.h>

Enemy::Enemy(std::string name, int health, int energy, int speed,
             std::vector<Attack> attacks) {
  this->name = name;
  this->maxHealth = health;
  this->maxEnergy = energy;
  this->speed = speed;
  this->attacks = attacks;
}

void Enemy::draw(Rectangle pos) { DrawRectangleRec(pos, YELLOW); }

void Enemy::update() {}
