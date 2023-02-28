#pragma once

#include "combat-entity.h"
#include "raylib.h"

class Player : public CombatEntity {
  public:
    Player();

    void update() override;
    void updateCurrentTextureFrame() override;
    void setCurrentTexture() override;
};
