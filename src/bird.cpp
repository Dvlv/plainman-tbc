#include "headers/bird.h"
#include "headers/attack.h"
#include "raylib.h"
#include <iostream>
#include <vector>

Bird::Bird(Rectangle pos)
    : Enemy(pos, "Bird", "A small bird. Kind of cute.", 4, 2, 1,
            std::vector<Attack>{
                Attack("Zap", "A small zap", AttackType::SHOUT, 2, 1,
                       AttackElement::ELECTRIC),
                Attack("Kick", "An awkward kick", AttackType::PUNCH, 1, 0,
                       AttackElement::NONE),
            }) {}

void Bird::setCurrentTexture() {

  switch (this->currentAnimation) {

  case Animation::IDLE:
    // for some reason it segfaults if I do this in the constructor
    // this == 0 nonsense is the way to check if a map contains a val
    if (this->textures.count(Animation::IDLE) == 0) {
      this->textures[Animation::IDLE] =
          LoadTexture("src/assets/art/combat/enemies/bird/bird-idle.png");
    }

    this->currentTexture = this->textures[Animation::IDLE];
    break;

  case Animation::ATTACK:
  case Animation::MELEE_ATTACK:
    if (this->textures.count(Animation::ATTACK) == 0) {
      this->textures[Animation::ATTACK] =
          LoadTexture("src/assets/art/combat/enemies/bird/bird-walk.png");
      this->textures[Animation::MELEE_ATTACK] =
          LoadTexture("src/assets/art/combat/enemies/bird/bird-melee.png");
    }

    if (this->meleeAnimationState == MeleeAnimationState::ATTACKING) {
      this->currentTexture = this->textures[Animation::MELEE_ATTACK];
    } else {
      this->currentTexture = this->textures[Animation::ATTACK];
    }
    break;

  case Animation::CAST_ATTACK:
    if (this->textures.count(Animation::CAST_ATTACK) == 0) {
      this->textures[Animation::CAST_ATTACK] =
          LoadTexture("src/assets/art/combat/enemies/bird/bird-cast.png");
    }

    this->currentTexture = this->textures[Animation::CAST_ATTACK];
    break;

  case Animation::TAKE_DAMAGE:
    if (this->textures.count(Animation::TAKE_DAMAGE) == 0) {
      this->textures[Animation::TAKE_DAMAGE] =
          LoadTexture("src/assets/art/combat/enemies/bird/bird-takedmg.png");
    }

    this->currentTexture = this->textures[Animation::TAKE_DAMAGE];
    break;
  }
}

void Bird::draw(Texture2D currentTexture) {
  this->setCurrentTexture();
  Enemy::draw(this->currentTexture);
}

Bird::~Bird() {
  printf("bird dest\n");
  for (auto t : this->textures) {
    UnloadTexture(t.second);
  }
}
