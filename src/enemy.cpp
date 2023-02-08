#include "headers/enemy.h"
#include <iostream>
#include <raylib.h>
#include <vector>

Enemy::Enemy(Rectangle pos, std::string name, std::string description,
             int health, int energy, int speed, std::vector<Attack> attacks) {
  this->pos = pos;
  this->name = name;
  this->description = description;
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

  this->animationFrameCount = 0;
  this->currentanimationFrame = 0;
  this->textures = std::map<Animation, Texture2D>();
}

void Enemy::takeDamage(int dmg) {
  if (dmg > 0) {
    this->currentAnimation = Animation::TAKE_DAMAGE;
    this->currentanimationFrame = 0;

    this->currentHealth -= dmg;
  }
}

bool Enemy::isDead() { return this->currentHealth < 1; }

void Enemy::drawHealthBar() {
  constexpr int barWidth = 100;
  constexpr int barHeight = 20;
  constexpr int healthFontSize = 20;

  int hp_percent =
      ((float)this->currentHealth / (float)this->maxHealth) * 100.0f;

  DrawRectangle(this->pos.x, this->pos.y + 100 + 30, barWidth, barHeight, RED);

  DrawRectangle(this->pos.x, this->pos.y + 100 + 30, hp_percent, barHeight,
                DARKGREEN);

  std::string healthText = std::to_string(this->currentHealth) + "/" +
                           std::to_string(this->maxHealth);

  int textWidth = MeasureText(healthText.c_str(), healthFontSize);

  DrawText(healthText.c_str(), this->pos.x + (barWidth / 2) - (textWidth / 2),
           this->pos.y + 100 + 30, healthFontSize, WHITE);
}

void Enemy::drawEnergyBar() {
  constexpr int barWidth = 100;
  constexpr int barHeight = 20;
  constexpr int energyFontSize = 20;
  constexpr int energyBarPosBelowPlayer = 160;

  int ePercent = ((float)this->currentEnergy / (float)this->maxEnergy) * 100.0f;

  DrawRectangle(this->pos.x, this->pos.y + energyBarPosBelowPlayer, barWidth,
                barHeight, RED);

  DrawRectangle(this->pos.x, this->pos.y + energyBarPosBelowPlayer, ePercent,
                barHeight, DARKBLUE);

  std::string energyText = std::to_string(this->currentEnergy) + "/" +
                           std::to_string(this->maxEnergy);

  int textWidth = MeasureText(energyText.c_str(), energyFontSize);

  DrawText(energyText.c_str(), this->pos.x + (barWidth / 2) - (textWidth / 2),
           this->pos.y + energyBarPosBelowPlayer, energyFontSize, WHITE);
}

void Enemy::performAttack(Attack *atk, Rectangle targetBounds,
                          bool *animationPlaying, bool *doAttack) {
  // Plays attack animation, hands control back to GameState

  // get animation to play based on attack type
  this->currentAnimation = Animation::ATTACK;
  // TODO look up animation frames from vector

  //*animationPlaying = false;
  this->animationPlaying = animationPlaying;
  this->attackTarget = targetBounds;
  this->currentAttack = atk;
  this->doAttack = doAttack;

  if (atk->energyCost > 0) {
    this->currentEnergy -= atk->energyCost;
  }
}

Attack *Enemy::selectBestAttack() {
  int highestDmg = 0;
  Attack *bestAttack = &this->attacks[0];

  for (Attack &a : this->attacks) {
    if (a.damage > highestDmg && a.energyCost <= this->currentEnergy) {
      highestDmg = a.damage;
      bestAttack = &a;
    }
  }

  return bestAttack;
}

void Enemy::draw(Texture2D currentTexture) {
  const int spriteSize = 128;

  if (this->isDead()) {
    // play death anim then mark canBeDeleted
    Rectangle currentSpriteWindow =
        Rectangle{(float)spriteSize * this->currentanimationFrame, spriteSize,
                  spriteSize, spriteSize};

    DrawTextureRec(this->currentTexture, currentSpriteWindow,
                   Vector2{this->pos.x, this->pos.y}, Color{255, 0, 0, 128});
    this->canBeDeleted = true;

    return;
  }

  Color tint = this->currentAnimation == Animation::TAKE_DAMAGE ? RED : WHITE;

  // passed from derived class
  this->currentTexture = currentTexture;

  Rectangle currentSpriteWindow =
      Rectangle{(float)spriteSize * this->currentanimationFrame, spriteSize,
                spriteSize, spriteSize};

  DrawTextureRec(this->currentTexture, currentSpriteWindow,
                 Vector2{this->pos.x, this->pos.y}, tint);

  if (this->currentAnimation != Animation::ATTACK &&
      this->currentAnimation != Animation::CAST_ATTACK) {
    drawHealthBar();
    drawEnergyBar();
  }
}

void Enemy::update() {
  this->updateCurrentTextureFrame();

  constexpr int movementSteps = 15;
  if (this->currentAnimation == Animation::ATTACK &&
      (this->currentAttack->atkType == AttackType::PUNCH ||
       this->currentAttack->atkType == AttackType::KICK)) {
    if (this->meleeAnimationState == MeleeAnimationState::FORWARD) {
      // move to player
      if (this->pos.x > (this->attackTarget.x + 100)) {
        this->pos.x -= movementSteps;
      } else {
        // reached enemy, play melee anim
        this->meleeAnimationState = MeleeAnimationState::ATTACKING;
        this->currentanimationFrame = 0;
      }
    } else if (this->meleeAnimationState == MeleeAnimationState::BACKWARD) {
      // move back to original position
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
  } else {
    if (this->currentAnimation == Animation::ATTACK) {
      this->currentAnimation = Animation::CAST_ATTACK;
      this->currentanimationFrame = 0;
    }
  }
}

void Enemy::updateCurrentTextureFrame() {
  // TODO switch statement
  if (this->currentAnimation == Animation::IDLE) {
    const int idleFrameSwap = 30; // 2FPS
    const int idleFrameCount = 3;

    this->animationFrameCount += 1;
    if (this->animationFrameCount > idleFrameSwap) {
      this->animationFrameCount = 0;

      this->currentanimationFrame += 1;

      if (this->currentanimationFrame > idleFrameCount) {
        this->currentanimationFrame = 1;
      }
    }
  } else if (this->currentAnimation == Animation::ATTACK) {
    if (this->meleeAnimationState == MeleeAnimationState::ATTACKING) {
      const int attackFrameSwap = 8; // 15FPS
      const int attackFrameCount = 4;

      this->animationFrameCount += 1;
      if (this->animationFrameCount > attackFrameSwap) {
        this->animationFrameCount = 0;

        this->currentanimationFrame += 1;

        if (this->currentanimationFrame > attackFrameCount) {
          // move on to backwards
          this->meleeAnimationState = MeleeAnimationState::BACKWARD;
          this->currentanimationFrame = 0;
          *this->doAttack = true;
        }
      }
    } else {
      // moving fwd or bw, use walk anim
      const int walkFrameSwap = 8; // 4FPS
      const int walkFrameCount = 2;

      this->animationFrameCount += 1;
      if (this->animationFrameCount > walkFrameSwap) {
        this->animationFrameCount = 0;

        this->currentanimationFrame += 1;

        if (this->currentanimationFrame > walkFrameCount) {
          this->currentanimationFrame = 0;
        }
      }
    }
  } else if (this->currentAnimation == Animation::CAST_ATTACK) {
    const int attackFrameSwap = 6; // 15FPS
    const int attackFrameCount = 4;

    this->animationFrameCount += 1;
    if (this->animationFrameCount > attackFrameSwap) {
      this->animationFrameCount = 0;

      this->currentanimationFrame += 1;

      // third frame signal to apply damage
      if (this->currentanimationFrame == 1) {
        *this->doAttack = true;
      }

      // signal the attack is finished
      if (this->currentanimationFrame > attackFrameCount) {
        this->currentAnimation = Animation::IDLE;
        *this->animationPlaying = false;
      }
    }
  } else if (this->currentAnimation == Animation::TAKE_DAMAGE) {
    const int dmgFrameSwap = 3;
    const int dmgFrameCount = 4;

    this->animationFrameCount += 1;
    if (this->animationFrameCount > dmgFrameSwap) {
      this->animationFrameCount = 0;

      this->currentanimationFrame += 1;

      if (this->currentanimationFrame > dmgFrameCount) {
        this->currentAnimation = Animation::IDLE;
      }
    }
  }
}

Enemy::~Enemy() { printf("enemy dest\n"); }
