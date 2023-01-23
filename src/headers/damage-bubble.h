#pragma once

#include "raylib.h"

class DamageBubble {
private:
  Rectangle pos;

  int damageNumber;
  int lifetime;
  int currentFrameCount;

public:
  DamageBubble(Rectangle pos, int damageNumber);

  bool canBeDeleted;

  void update();
  void draw();
};
