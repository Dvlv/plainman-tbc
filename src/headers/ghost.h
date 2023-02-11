#pragma once

#include "enemy.h"

class Ghost : public Enemy {
private:
  Rectangle attackTarget;
  Rectangle startingPos;
  bool *animationPlaying;

  std::map<Animation, Texture2D> textures;
  Texture2D currentTexture;
  int animationFrameCount;
  int currentanimationFrame;

public:
  Ghost(Rectangle pos);

  virtual void setCurrentTexture() override;
  virtual void draw(Texture2D currentTexture = Texture2D()) override;
  virtual ~Ghost() override;
};
