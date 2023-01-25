#pragma once

#include "attack.h"
#include "raylib.h"

class CastEffect {
private:
  Rectangle pos;

  int damageNumber;
  int lifetime;
  int currentFrameCount;

  Texture2D sprite;

  bool spriteLoaded;

  AttackElement element;

public:
  CastEffect(Rectangle pos, AttackElement element);

  bool canBeDeleted;

  void loadSprite();

  void update();
  void draw();

  ~CastEffect();
};
