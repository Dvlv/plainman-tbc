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

  Attack *currentAttack;

  Rectangle attackTarget;
  Rectangle startingPos;
  bool *animationPlaying;
  MeleeAnimationState meleeAnimationState;

public:
  Enemy(Rectangle pos, std::string name, int health, int energy, int speed,
        std::vector<Attack> attacks);
  bool isDead();
  bool canBeDeleted;
  Rectangle pos;

  void drawHealthBar();
  void draw();

  void performAttack(Attack *atk, Rectangle targetBounds,
                     bool *animationPlaying);
  Attack *selectBestAttack();
  void takeDamage(int dmg);

  void update();

  virtual ~Enemy() = default;
};
