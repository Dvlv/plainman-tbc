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
  this->startingPos = pos;
  this->currentAnimation = Animation::IDLE;
  this->meleeAnimationState = MeleeAnimationState::FORWARD;
}

std::vector<Attack> *Player::getAttacks() { return &this->attacks; }

void Player::addAttack(Attack a) { this->attacks.push_back(a); }

void Player::performAttack(Attack *atk, Rectangle targetBounds,
                           bool *animationPlaying) {
  // Plays attack animation, hands control back to GameState

  // get animation to play based on attack type
  this->currentAnimation = Animation::ATTACK;
  // TODO look up animation frames from vector

  //*animationPlaying = false;
  this->animationPlaying = animationPlaying;
  this->attackTarget = targetBounds;
  this->currentAttack = atk;
}

void Player::takeDamage(int dmg) { this->currentHealth -= dmg; }

void Player::drawHealthBar() {
  constexpr int barWidth = 100;
  constexpr int barHeight = 20;
  constexpr int healthFontSize = 20;

  int hpPercent =
      ((float)this->currentHealth / (float)this->maxHealth) * 100.0f;

  DrawRectangle(this->pos.x, this->pos.y + 100 + 30, barWidth, barHeight, RED);

  DrawRectangle(this->pos.x, this->pos.y + 100 + 30, hpPercent, barHeight,
                DARKGREEN);

  std::string healthText = std::to_string(this->currentHealth) + "/" +
                           std::to_string(this->maxHealth);

  int textWidth = MeasureText(healthText.c_str(), healthFontSize);

  DrawText(healthText.c_str(), this->pos.x + (barWidth / 2) - (textWidth / 2),
           this->pos.y + 100 + 30, healthFontSize, WHITE);
}

void Player::draw() {
  DrawRectangleRec(this->pos, RAYWHITE);
  drawHealthBar();
}

void Player::update() {
  // TODO logic for timing animation frames
  // TODO attack class needs melee vs cast
  // TODO movementSteps can overshoot, clamp to distance if <30
  constexpr int movementSteps = 30;
  if (this->currentAnimation == Animation::ATTACK &&
      (this->currentAttack->atkType == AttackType::PUNCH ||
       this->currentAttack->atkType == AttackType::KICK)) {
    if (this->meleeAnimationState == MeleeAnimationState::FORWARD) {
      // move to enemy
      if (this->pos.x < this->attackTarget.x) {
        this->pos.x += movementSteps;
      } else {
        // reached enemy
        // TODO play punch animation
        this->meleeAnimationState = MeleeAnimationState::ATTACKING;
      }
    } else if (this->meleeAnimationState == MeleeAnimationState::ATTACKING) {
      // TODO play animation
      this->meleeAnimationState = MeleeAnimationState::BACKWARD;
    } else {
      // move back to starting position
      if (this->pos.x > this->startingPos.x) {
        this->pos.x -= movementSteps;
      } else {
        // reached starting position
        this->pos.x = this->startingPos.x;
        this->meleeAnimationState = MeleeAnimationState::FORWARD;
        this->currentAnimation = Animation::IDLE;
        *this->animationPlaying = false;
      }
    }
  } else {
    if (this->currentAnimation == Animation::ATTACK) {
      // TODO play cast animation
      this->currentAnimation = Animation::IDLE;
      *this->animationPlaying = false;
    }
  }
}
