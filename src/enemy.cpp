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
  this->pos = pos;
  this->startingPos = pos;
  this->meleeAnimationState = MeleeAnimationState::FORWARD;
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

  //*animationPlaying = false;
  this->animationPlaying = animationPlaying;
  this->attackTarget = targetBounds;
  this->currentAttack = atk;
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

void Enemy::update() {
  // GetFrameTime();

  // TODO logic for timing animation frames
  // TODO attack class needs melee vs cast
  // TODO movementSteps can overshoot, clamp to distance if <30
  constexpr int movementSteps = 30;
  if (this->currentAnimation == Animation::ATTACK &&
      this->currentAttack->atkType == AttackType::KICK) {
    if (this->meleeAnimationState == MeleeAnimationState::FORWARD) {
      // move to enemy
      if (this->pos.x > this->attackTarget.x) {
        this->pos.x -= movementSteps;
      } else {
        // reached player
        // TODO play punch animation
        this->meleeAnimationState = MeleeAnimationState::ATTACKING;
      }
    } else if (this->meleeAnimationState == MeleeAnimationState::ATTACKING) {
      // TODO play animation
      this->meleeAnimationState = MeleeAnimationState::BACKWARD;
    } else {
      // move back to starting position
      if (this->pos.x < this->startingPos.x) {
        this->pos.x += movementSteps;
      } else {
        // reached starting position
        this->pos.x = this->startingPos.x;
        this->meleeAnimationState = MeleeAnimationState::FORWARD;
        this->currentAnimation = Animation::IDLE;
        *this->animationPlaying = false;
      }
    }
  }
}
