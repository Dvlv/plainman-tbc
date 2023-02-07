#pragma once

#include "raylib.h"

enum HealType {
  HEALTH_BUBBLE,
  ENERGY_BUBBLE,
};

class HealBubble {
private:
  Rectangle pos;

  HealType type;
  int number;
  int lifetime;
  int currentFrameCount;

public:
  HealBubble(Rectangle pos, int number, HealType type);

  bool canBeDeleted;

  void update();
  void draw();
};
