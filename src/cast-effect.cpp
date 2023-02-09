#include "headers/cast-effect.h"
#include "headers/texture-store.h"
#include "raylib.h"
#include <memory>

CastEffect::CastEffect(Rectangle pos, int textureId,
                       std::shared_ptr<TextureStore> textureStore) {
  this->pos = pos;
  this->lifetime = 30;
  this->currentFrameCount = 0;
  this->canBeDeleted = false;
  this->spriteLoaded = false;
  this->animFrameCount = 0;
  this->currentSpriteFrame = 0;
  this->textureStore = textureStore;
  this->textureId = textureId;
}

void CastEffect::loadSprite() {
  this->sprite = this->textureStore->getTexture(this->textureId);
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

CastEffect::~CastEffect() { printf("unloading cast effect\n"); }
