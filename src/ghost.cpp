#include "headers/ghost.h"
#include "headers/attack.h"
#include "raylib.h"
#include <iostream>
#include <vector>

Ghost::Ghost(Rectangle pos)
    : Enemy(pos, "Ghost", "A spooky ghost", 3, 6, 1,
            std::vector<Attack>{
                Attack("Chill", "A ghostly chill", AttackType::SHOUT, 2, 2,
                       AttackElement::ICE),
                Attack("Spook", "A scary noise", AttackType::SHOUT, 1, 0,
                       AttackElement::NONE),
            }) {}

void Ghost::setCurrentTexture() {

  switch (this->currentAnimation) {

  case Animation::IDLE:
    // for some reason it segfaults if I do this in the constructor
    // this == 0 nonsense is the way to check if a map contains a val
    if (this->textures.count(Animation::IDLE) == 0) {
      this->textures[Animation::IDLE] =
          LoadTexture("src/assets/art/combat/enemies/ghost/ghost-idle.png");
    }

    this->currentTexture = this->textures[Animation::IDLE];
    break;

  case Animation::ATTACK:
  case Animation::MELEE_ATTACK:
    if (this->textures.count(Animation::ATTACK) == 0) {
      this->textures[Animation::ATTACK] =
          LoadTexture("src/assets/art/combat/enemies/ghost/ghost-walk.png");
      this->textures[Animation::MELEE_ATTACK] =
          LoadTexture("src/assets/art/combat/enemies/ghost/ghost-cast.png");
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
          // ghost cant cast
          LoadTexture("src/assets/art/combat/enemies/ghost/ghost-cast.png");
    }

    this->currentTexture = this->textures[Animation::CAST_ATTACK];
    break;

  case Animation::TAKE_DAMAGE:
    if (this->textures.count(Animation::TAKE_DAMAGE) == 0) {
      this->textures[Animation::TAKE_DAMAGE] =
          LoadTexture("src/assets/art/combat/enemies/ghost/ghost-takedmg.png");
    }

    this->currentTexture = this->textures[Animation::TAKE_DAMAGE];
    break;
  }
}

void Ghost::draw(Texture2D currentTexture) {
  this->setCurrentTexture();
  Enemy::draw(this->currentTexture);
}

Ghost::~Ghost() {
  for (auto t : this->textures) {
    UnloadTexture(t.second);
  }
  printf("ghost dest\n");
}
