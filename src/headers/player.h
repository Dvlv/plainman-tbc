#pragma once

#include "animation.h"
#include "attack.h"
#include "raylib.h"
#include <functional>
#include <map>
#include <vector>

class Player {
private:
  Animation currentAnimation;
  Animation previousAnimation;

  int maxHealth;

  int maxEnergy;

  int speed;

  std::vector<Attack> attacks;

  Rectangle startingPos;
  Attack *currentAttack;
  Rectangle attackTarget;
  bool *animationPlaying;
  MeleeAnimationState meleeAnimationState;

  std::map<Animation, Texture2D> textures;
  Texture2D currentTexture;
  int animationFrameCount;
  int currentanimationFrame;

  bool *doAttack;

public:
  Player(Rectangle pos, int health, int energy);

  int currentHealth;
  int currentEnergy;
  Rectangle pos;

  void addAttack(Attack a);

  void performAttack(Attack *attack, Rectangle targetBounds,
                     bool *animationPlaying, bool *doAttack);

  std::vector<Attack> *getAttacks();

  void takeDamage(int dmg);

  void drawHealthBar();
  void drawEnergyBar();

  void updateCurrentTextureFrame();
  void setCurrentTexture();

  void draw();
  void update();

  ~Player();
};
