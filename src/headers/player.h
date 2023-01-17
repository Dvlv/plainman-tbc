#pragma once

#include "animation.h"
#include "attack.h"
#include "raylib.h"
#include <vector>

enum MeleeAnimationState {
  FORWARD,
  ATTACKING,
  BACKWARD,
};

class Player {
private:
  Animation currentAnimation;
  Animation previousAnimation;

  int maxHealth;
  int currentHealth;

  int maxEnergy;
  int currentEnergy;

  int speed;

  std::vector<Attack> attacks;

  Rectangle startingPos;
  Attack *currentAttack;
  Rectangle attackTarget;
  bool *animationPlaying;
  MeleeAnimationState meleeAnimationState;

public:
  Player(Rectangle pos, int health, int energy);

  Rectangle pos;

  void addAttack(Attack a);

  void performAttack(Attack *attack, Rectangle targetBounds,
                     bool *animationPlaying);

  std::vector<Attack> *getAttacks();

  void takeDamage(int dmg);

  void drawHealthBar();

  void draw();
  void update();
};
