#pragma once

#include "enemy.h"

class Bird : public Enemy {
private:
  Rectangle attackTarget;
  Rectangle startingPos;
  bool *animationPlaying;

  std::map<Animation, Texture2D> textures;
  Texture2D currentTexture;
  int animationFrameCount;
  int currentanimationFrame;

public:
  Bird(Rectangle pos);

  virtual void setCurrentTexture() override;
  virtual void draw(Texture2D currentTexture = Texture2D()) override;
  virtual ~Bird() override;
};
