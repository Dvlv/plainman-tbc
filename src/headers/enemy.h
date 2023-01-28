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

  std::map<Animation, Texture2D> textures;
  Texture2D currentTexture;
  int animationFrameCount;
  int currentanimationFrame;

  bool *doAttack;

  virtual void setCurrentTexture() = 0;

public:
  Enemy(Rectangle pos, std::string name, std::string description, int health,
        int energy, int speed, std::vector<Attack> attacks);
  std::string description;
  Rectangle pos;
  bool canBeDeleted;
  Animation currentAnimation;
  MeleeAnimationState meleeAnimationState;

  bool isDead();
  void drawHealthBar();

  void performAttack(Attack *atk, Rectangle targetBounds,
                     bool *animationPlaying, bool *doAttack);
  Attack *selectBestAttack();
  void takeDamage(int dmg);

  void updateCurrentTextureFrame();

  virtual void draw(Texture2D currentTexture = Texture2D());

  void update();

  virtual ~Enemy();
};
