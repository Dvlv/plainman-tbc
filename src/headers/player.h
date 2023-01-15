#pragma once

#include "animation.h"
#include "attack.h"
#include "raylib.h"
#include <vector>

class Player {
private:
  Animation currentAnimation;
  Animation previousAnimation;

  Rectangle pos;

  int maxHealth;
  int currentHealth;

  int maxEnergy;
  int currentEnergy;

  int speed;

  std::vector<Attack> attacks;

public:
  Player(Rectangle pos, int health, int energy);

  void addAttack(Attack a);

  void performAttack(Attack *attack, Rectangle targetBounds,
                     bool *animationStillPlaying);

  std::vector<Attack> *getAttacks();

  void takeDamage(int dmg);

  void draw();
  void update();
};
