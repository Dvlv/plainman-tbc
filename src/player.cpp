#include "headers/player.h"
#include "headers/animation.h"
#include "headers/attack.h"
#include "raylib.h"
#include <cmath>
#include <vector>

Player::Player(Rectangle pos, int health, int energy) {
  this->maxHealth = health;
  this->currentHealth = health;
  this->maxEnergy = energy;
  this->currentEnergy = energy;
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

void Player::drawHealthBar() {
  // calculate health as percentage
  int hp_percent =
      ((float)this->currentHealth / (float)this->maxHealth) * 100.0f;

  // draw rectangle of width 100
  DrawRectangle(this->pos.x, this->pos.y + 100 + 30, 100, 10, RED);

  // draw green rectangle the length of the hp percentage
  DrawRectangle(this->pos.x, this->pos.y + 100 + 30, hp_percent, 10, BLUE);
  printf("%d, %d, %d\n", this->currentHealth, this->maxHealth, hp_percent);
}

void Player::draw() {
  DrawRectangleRec(this->pos, RAYWHITE);
  // draw health bar
  drawHealthBar();
}

void Player::update() {}
