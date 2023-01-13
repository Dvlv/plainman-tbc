#include "headers/player.h"
#include "headers/attack.h"
#include "raylib.h"
#include <vector>

Player::Player(int health, int energy) {
  this->maxHealth = health;
  this->maxEnergy = energy;
  this->attacks = std::vector<Attack>();
}

void Player::addAttack(Attack a) { this->attacks.push_back(a); }

void Player::draw(Rectangle pos) { DrawRectangleRec(pos, RAYWHITE); }
