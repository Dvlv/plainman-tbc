#pragma once

#include "animation.h"
#include "attack.h"
#include "raylib.h"
#include <map>
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

  std::map<Animation, Texture2D> textures;
  Texture2D currentTexture;
  int animationFrameCount;
  int currentanimationFrame;

public:
  Enemy(Rectangle pos, std::string name, std::string description, int health,
        int energy, int speed, std::vector<Attack> attacks);
  std::string description;
  Rectangle pos;
  bool canBeDeleted;

  bool isDead();
  void drawHealthBar();

  void performAttack(Attack *atk, Rectangle targetBounds,
                     bool *animationPlaying);
  Attack *selectBestAttack();
  void takeDamage(int dmg);

  void updateCurrentTextureFrame();
  void setCurrentTexture();

  void draw();
  void update();

  virtual ~Enemy() = default;
};
