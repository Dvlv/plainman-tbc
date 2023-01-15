#include "headers/player.h"
#include "headers/animation.h"
#include "headers/attack.h"
#include "raylib.h"
#include <vector>

Player::Player(Rectangle pos, int health, int energy) {
  this->maxHealth = health;
  this->maxEnergy = energy;
  this->attacks = std::vector<Attack>();
  this->pos = pos;
}

std::vector<Attack> *Player::getAttacks() { return &this->attacks; }

void Player::addAttack(Attack a) { this->attacks.push_back(a); }

void Player::performAttack(Attack *atk, Rectangle targetBounds,
                           bool *animationPlaying) {
  // Plays attack animation,
  // hands control back to GameState
  printf("Performing atk: %s\n", atk->name.c_str());
  // get animation to play based on attack type
  this->currentAnimation = Animation::ATTACK;
  // TODO look up animation frames from vector

  *animationPlaying = false;
}

void Player::takeDamage(int dmg) { this->currentHealth -= dmg; }

void Player::draw() { DrawRectangleRec(this->pos, RAYWHITE); }

void Player::update() {}
