#include "headers/turtle.h"
#include "headers/attack.h"
#include "raylib.h"
#include <iostream>
#include <vector>

Turtle::Turtle(Rectangle pos)
    : Enemy(pos, "Turtle", "A small turtle. Kind of cute.", 2, 0, 1,
            std::vector<Attack>{
                Attack("Bite", "A small bite", AttackType::KICK, 1, 0),
            }) {}

void Turtle::setCurrentTexture() {

  switch (this->currentAnimation) {

  case Animation::IDLE:
    // for some reason it segfaults if I do this in the constructor
    // this == 0 nonsense is the way to check if a map contains a val
    if (this->textures.count(Animation::IDLE) == 0) {
      this->textures[Animation::IDLE] =
          LoadTexture("src/assets/art/combat/enemies/turtle/turtle-idle.png");
    }

    this->currentTexture = this->textures[Animation::IDLE];
    break;

  case Animation::ATTACK:
  case Animation::MELEE_ATTACK:
    if (this->textures.count(Animation::ATTACK) == 0) {
      this->textures[Animation::ATTACK] =
          LoadTexture("src/assets/art/combat/enemies/turtle/turtle-walk.png");
      this->textures[Animation::MELEE_ATTACK] =
          LoadTexture("src/assets/art/combat/enemies/turtle/turtle-melee.png");
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
          // turtle cant cast
          LoadTexture("src/assets/art/combat/enemies/turtle/turtle-melee.png");
    }

    this->currentTexture = this->textures[Animation::CAST_ATTACK];
    break;

  case Animation::TAKE_DAMAGE:
    if (this->textures.count(Animation::TAKE_DAMAGE) == 0) {
      this->textures[Animation::TAKE_DAMAGE] = LoadTexture(
          "src/assets/art/combat/enemies/turtle/turtle-takedmg.png");
    }

    this->currentTexture = this->textures[Animation::TAKE_DAMAGE];
    break;
  }
}

void Turtle::draw(Texture2D currentTexture) {
  this->setCurrentTexture();
  Enemy::draw(this->currentTexture);
}

Turtle::~Turtle() {
  printf("turt dest\n");
  for (auto t : this->textures) {
    UnloadTexture(t.second);
  }
}
