#pragma once

#include "attack.h"
#include "raylib.h"
#include <vector>

enum Animation {
  IDLE,
  ATTACK,
};

class Player {
private:
  Animation currentAnimation;
  int health;
  int energy;
  std::vector<Attack> attacks;

public:
  void draw(Rectangle pos);
  void update();

  void addAttack(Attack a);

  Player(int health, int energy);
};
