#pragma once

#include "animation.h"
#include "attack.h"
#include "raylib.h"
#include <functional>
#include <map>
#include <vector>

struct PlayerCombatData {
  int maxHealth;
  int maxEnergy;
  int currentHealth;
  int currentEnergy;
  std::vector<Attack> *attacks;
  int skillPoints;
};

class Player {
private:
  Animation currentAnimation;
  Animation previousAnimation;

  // combat data
  int maxHealth;
  int maxEnergy;
  std::vector<Attack> *attacks;

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
  Player(Rectangle pos, PlayerCombatData combatData);

  int currentHealth;
  int currentEnergy;
  Rectangle pos;

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
