#include "headers/enemy.h"
#include <raylib.h>

Enemy::Enemy(Rectangle pos, std::string name, int health, int energy, int speed,
             std::vector<Attack> attacks) {
  this->pos = pos;
  this->name = name;
  this->maxHealth = health;
  this->currentHealth = health;
  this->maxEnergy = energy;
  this->currentEnergy = energy;
  this->speed = speed;
  this->attacks = attacks;
  this->canBeDeleted = false;
  this->currentAnimation = Animation::IDLE;
}

void Enemy::takeDamage(int dmg) { this->currentHealth -= dmg; }

bool Enemy::isDead() { return this->currentHealth < 1; }

void Enemy::drawHealthBar() {
  int hp_percent =
      ((float)this->currentHealth / (float)this->maxHealth) * 100.0f;

  DrawRectangle(this->pos.x, this->pos.y + 100 + 30, 100, 10, RED);

  DrawRectangle(this->pos.x, this->pos.y + 100 + 30, hp_percent, 10, BLUE);
}

void Enemy::performAttack(Attack *atk, Rectangle targetBounds,
                          bool *animationPlaying) {
  // Plays attack animation, hands control back to GameState

  // get animation to play based on attack type
  this->currentAnimation = Animation::ATTACK;
  // TODO look up animation frames from vector

  *animationPlaying = false;
}

Attack *Enemy::selectBestAttack() {
  int highestDmg = 0;
  Attack *bestAttack = &this->attacks[0];

  for (Attack &a : this->attacks) {
    if (a.damage > highestDmg) {
      highestDmg = a.damage;
      bestAttack = &a;
    }
  }

  printf("best attack: %s\n", bestAttack->name.c_str());
  return bestAttack;
}

void Enemy::draw() {
  if (this->isDead()) {
    // play death anim then mark canBeDeleted
    DrawRectangleRec(this->pos, RED);
    this->canBeDeleted = true;
  } else {
    DrawRectangleRec(this->pos, YELLOW);
    drawHealthBar();
  }
}

void Enemy::update() { GetFrameTime(); }
