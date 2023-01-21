#include "headers/player.h"
#include "headers/animation.h"
#include "headers/attack.h"
#include "raylib.h"
#include <cmath>
#include <map>
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

  this->animationFrameCount = 0;
  this->currentanimationFrame = 0;
  this->textures = std::map<Animation, Texture2D>();
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
  if (this->currentAnimation == Animation::IDLE) {
    // for some reason it segfaults if I do this in the constructor
    // this == 0 nonsense is the way to check if a map contains a val
    if (this->textures.count(Animation::IDLE) == 0) {
      this->textures[Animation::IDLE] =
          LoadTexture("src/assets/art/combat/player/player-idle.png");

      this->currentTexture = this->textures[Animation::IDLE];
    }

    Rectangle currentSpriteWindow =
        Rectangle{64.0f * this->currentanimationFrame, 64, 64, 64};

    DrawTextureRec(this->currentTexture, currentSpriteWindow,
                   Vector2{this->pos.x, this->pos.y}, WHITE);
  } else {
    DrawRectangleRec(this->pos, RAYWHITE);
  }
  drawHealthBar();
}

void Player::update() {
  // TODO logic for timing animation frames
  // TODO attack class needs melee vs cast
  // TODO movementSteps can overshoot, clamp to distance if <30

  if (this->currentAnimation == Animation::IDLE) {
    const int idleFrameSwap = 10; // 6FPS
    const int idleFrameCount = 2;

    this->animationFrameCount += 1;
    if (this->animationFrameCount >= idleFrameSwap) {
      this->animationFrameCount = 0;

      this->currentanimationFrame += 1;

      if (this->currentanimationFrame > idleFrameCount) {
        this->currentanimationFrame = 0;
      }
    }
  }

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

Player::~Player() { UnloadTexture(this->textures[Animation::IDLE]); }
