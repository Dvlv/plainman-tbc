#include "headers/player.h"
#include "headers/animation.h"
#include "headers/attack.h"
#include "headers/combatstate.h"
#include "raylib.h"
#include <cmath>
#include <functional>
#include <map>
#include <memory>
#include <vector>

Player::Player(Rectangle pos, std::shared_ptr<PlayerCombatData> combatData) {
  this->maxHealth = combatData->maxHealth;
  this->currentHealth = combatData->currentHealth;
  this->maxEnergy = combatData->maxEnergy;
  this->currentEnergy = combatData->currentEnergy;
  this->attacks = combatData->attacks;
  this->pos = pos;
  this->startingPos = pos;
  this->currentAnimation = Animation::IDLE;
  this->meleeAnimationState = MeleeAnimationState::FORWARD;

  this->animationFrameCount = 0;
  this->currentanimationFrame = 0;
  this->textures = std::map<Animation, Texture2D>();
}

std::shared_ptr<std::vector<Attack>> Player::getAttacks() {
  return this->attacks;
}

void Player::performAttack(Attack *atk, Rectangle targetBounds,
                           bool *animationPlaying, bool *doAttack) {
  // Plays attack animation, hands control back to GameState

  // get animation to play based on attack type
  this->currentAnimation = Animation::ATTACK;
  // TODO look up animation frames from vector

  //*animationPlaying = false;
  this->animationPlaying = animationPlaying;
  this->attackTarget = targetBounds;
  this->currentAttack = atk;
  this->currentEnergy -= atk->energyCost;

  this->doAttack = doAttack;
}

void Player::takeDamage(int dmg) {
  this->currentAnimation = Animation::TAKE_DAMAGE;
  this->currentanimationFrame = 0;

  this->currentHealth -= dmg;
}

void Player::drawHealthBar() {
  constexpr int barWidth = 100;
  constexpr int barHeight = 20;
  constexpr int healthFontSize = 20;
  constexpr int healthBarPosBelowPlayer = 130;

  int hpPercent =
      ((float)this->currentHealth / (float)this->maxHealth) * 100.0f;

  DrawRectangle(this->pos.x, this->pos.y + healthBarPosBelowPlayer, barWidth,
                barHeight, RED);

  DrawRectangle(this->pos.x, this->pos.y + healthBarPosBelowPlayer, hpPercent,
                barHeight, DARKGREEN);

  std::string healthText = std::to_string(this->currentHealth) + "/" +
                           std::to_string(this->maxHealth);

  int textWidth = MeasureText(healthText.c_str(), healthFontSize);

  DrawText(healthText.c_str(), this->pos.x + (barWidth / 2) - (textWidth / 2),
           this->pos.y + healthBarPosBelowPlayer, healthFontSize, WHITE);
}

void Player::drawEnergyBar() {
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

void Player::draw() {
  const int spriteSize = 128;

  setCurrentTexture();

  // DrawRectangleRec(this->pos, RAYWHITE);
  //
  Color tint = this->currentAnimation == Animation::TAKE_DAMAGE ? RED : WHITE;

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

void Player::update() {
  // TODO logic for timing animation frames
  // TODO attack class needs melee vs cast
  // TODO movementSteps can overshoot, clamp to distance if <30

  this->updateCurrentTextureFrame();

  constexpr int movementSteps = 15;
  if (this->currentAnimation == Animation::ATTACK &&
      (this->currentAttack->atkType == AttackType::PUNCH ||
       this->currentAttack->atkType == AttackType::KICK)) {
    if (this->meleeAnimationState == MeleeAnimationState::FORWARD) {
      // move to enemy
      if (this->pos.x < (this->attackTarget.x - 100)) {
        this->pos.x += movementSteps;
      } else {
        // reached enemy, play melee anim
        this->meleeAnimationState = MeleeAnimationState::ATTACKING;
        this->currentanimationFrame = 0;
      }
    } else if (this->meleeAnimationState == MeleeAnimationState::BACKWARD) {
      // move back to original position
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
      // TODO signal to combatstate to draw element on targeted enemy
      this->currentAnimation = Animation::CAST_ATTACK;
      this->currentanimationFrame = 0;
    }
  }
}

void Player::updateCurrentTextureFrame() {
  // TODO switch statement
  if (this->currentAnimation == Animation::IDLE) {
    const int idleFrameSwap = 30; // 2FPS
    const int idleFrameCount = 2;

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
      const int attackFrameSwap = 4; // 15FPS
      const int attackFrameCount = 8;

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
      const int walkFrameSwap = 4; // 4FPS
      const int walkFrameCount = 4;

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
    const int attackFrameSwap = 3; // 15FPS
    const int attackFrameCount = 8;

    this->animationFrameCount += 1;
    if (this->animationFrameCount > attackFrameSwap) {
      this->animationFrameCount = 0;

      this->currentanimationFrame += 1;

      // second frame signal to apply damage
      if (this->currentanimationFrame == 3) {
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

void Player::setCurrentTexture() {
  // TODO switch statement

  if (this->currentAnimation == Animation::IDLE) {
    // for some reason it segfaults if I do this in the constructor
    // this == 0 nonsense is the way to check if a map contains a val
    if (this->textures.count(Animation::IDLE) == 0) {
      this->textures[Animation::IDLE] =
          LoadTexture("src/assets/art/combat/player/player-idle.png");
    }

    this->currentTexture = this->textures[Animation::IDLE];

  } else if (this->currentAnimation == Animation::ATTACK) {
    if (this->textures.count(Animation::ATTACK) == 0) {
      this->textures[Animation::ATTACK] =
          LoadTexture("src/assets/art/combat/player/player-walk.png");
      this->textures[Animation::MELEE_ATTACK] =
          LoadTexture("src/assets/art/combat/player/player-melee.png");
    }

    if (this->meleeAnimationState == MeleeAnimationState::ATTACKING) {
      this->currentTexture = this->textures[Animation::MELEE_ATTACK];
    } else {
      this->currentTexture = this->textures[Animation::ATTACK];
    }

  } else if (this->currentAnimation == Animation::CAST_ATTACK) {
    if (this->textures.count(Animation::CAST_ATTACK) == 0) {
      this->textures[Animation::CAST_ATTACK] =
          LoadTexture("src/assets/art/combat/player/player-cast.png");
    }

    this->currentTexture = this->textures[Animation::CAST_ATTACK];
  } else if (this->currentAnimation == Animation::TAKE_DAMAGE) {
    if (this->textures.count(Animation::TAKE_DAMAGE) == 0) {
      this->textures[Animation::TAKE_DAMAGE] =
          LoadTexture("src/assets/art/combat/player/player-takedmg.png");
    }

    this->currentTexture = this->textures[Animation::TAKE_DAMAGE];
  }
}

Player::~Player() {
  for (auto t : this->textures) {
    UnloadTexture(t.second);
  }
  printf("player destructor\n");
}
