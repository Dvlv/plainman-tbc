#pragma once

#include "attack.h"
#include "raylib.h"
#include "texture-store.h"
#include <memory>

class CastEffect {
private:
  Rectangle pos;

  int damageNumber;
  int lifetime;
  int currentFrameCount;
  int animFrameCount;
  int currentSpriteFrame;

  Texture2D sprite;
  int textureId;

  bool spriteLoaded;

  AttackElement element;

public:
  CastEffect(Rectangle pos, int textureId,
             std::shared_ptr<TextureStore> textureStore);

  std::shared_ptr<TextureStore> textureStore;

  bool canBeDeleted;

  void loadSprite();

  void update();
  void draw();

  ~CastEffect();
};
