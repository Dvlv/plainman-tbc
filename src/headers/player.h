#pragma once

#include "animation.h"
#include "attack.h"
#include "raylib.h"
#include <vector>

class Player {
private:
  Animation currentAnimation;

  int maxHealth;
  int currentHealth;

  int maxEnergy;
  int currentEnergy;

  int speed;

  std::vector<Attack> attacks;

public:
  Player(int health, int energy);

  void addAttack(Attack a);

  void performAttack(Attack *attack);

  std::vector<Attack> *getAttacks();

  void draw(Rectangle pos);
  void update();
};
