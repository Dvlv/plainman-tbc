#include "headers/cast-effect.h"
#include "raylib.h"

CastEffect::CastEffect(Rectangle pos, AttackElement element) {
  this->pos = pos;
  this->lifetime = 30;
  this->currentFrameCount = 0;
  this->canBeDeleted = false;
  this->element = element;
  this->spriteLoaded = false;
}

void CastEffect::loadSprite() {
  switch (this->element) {
  default:
    this->sprite = LoadTexture("src/assets/art/combat/attacks/cast-shout.png");
  }
  this->spriteLoaded = true;
}

void CastEffect::update() {
  if (!this->spriteLoaded) {
    this->loadSprite();
  }

  if (this->currentFrameCount >= this->lifetime) {
    this->canBeDeleted = true;
  }

  this->currentFrameCount++;
}

void CastEffect::draw() {
  if (!this->spriteLoaded) {
    this->loadSprite();
  }

  // TODO potentially animate
  DrawTexture(this->sprite, this->pos.x, this->pos.y,
              Color{255, 255, 255, 180});
}

CastEffect::~CastEffect() { UnloadTexture(this->sprite); }
