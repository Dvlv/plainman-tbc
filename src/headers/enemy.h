#pragma once

#include "animation.h"
#include "attack.h"
#include "raylib.h"
#include <string>
#include <vector>

class Enemy {
private:
  std::string name;

  Animation currentAnimation;

  std::vector<Attack> attacks;

  int currentHealth;
  int maxHealth;

  int currentEnergy;
  int maxEnergy;

  int speed;

public:
  Enemy(std::string name, int health, int energy, int speed,
        std::vector<Attack> attacks);
  void draw(Rectangle pos);
  void update();
  void performAttack(Attack *attack);
};
