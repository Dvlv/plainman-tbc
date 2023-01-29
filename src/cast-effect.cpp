#include "headers/cast-effect.h"
#include "raylib.h"

CastEffect::CastEffect(Rectangle pos, AttackElement element) {
  this->pos = pos;
  this->lifetime = 30;
  this->currentFrameCount = 0;
  this->canBeDeleted = false;
  this->element = element;
  this->spriteLoaded = false;
  this->texturePos = Rectangle{0, 0, 128, 128};
  this->animFrameCount = 0;
  this->currentSpriteFrame = 0;
}

void CastEffect::loadSprite() {
  switch (this->element) {
  case AttackElement::FIRE:
    this->sprite = LoadTexture("src/assets/art/combat/attacks/cast-fire.png");
    break;

  case AttackElement::ELECTRIC:
    this->sprite =
        LoadTexture("src/assets/art/combat/attacks/cast-electric.png");
    break;

  default:
    this->sprite = LoadTexture("src/assets/art/combat/attacks/cast-shout.png");
  }

  this->spriteLoaded = true;
}

void CastEffect::update() {
  if (!this->spriteLoaded) {
    this->loadSprite();
  }

  // get current frame
  const int frameCount = 2; // ALL atk sprites have 2 frames
  const int frameSwapSpeed = 6;

  if (this->animFrameCount >= frameSwapSpeed) {
    this->currentSpriteFrame = this->currentSpriteFrame == 0 ? 1 : 0;
    this->animFrameCount = 0;
  }

  if (this->currentFrameCount >= this->lifetime) {
    this->canBeDeleted = true;
  }

  this->currentFrameCount++;
  this->animFrameCount++;
}

void CastEffect::draw() {
  const int spriteSize = 128;

  if (!this->spriteLoaded) {
    this->loadSprite();
  }

  Rectangle currentSpriteWindow =
      Rectangle{(float)spriteSize * this->currentSpriteFrame, spriteSize,
                spriteSize, spriteSize};

  DrawTextureRec(this->sprite, currentSpriteWindow,
                 Vector2{this->pos.x, this->pos.y}, WHITE);
}

CastEffect::~CastEffect() { UnloadTexture(this->sprite); }
