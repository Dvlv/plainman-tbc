#pragma once

#include "attack.h"
#include "enums.h"
#include "raylib.h"
#include <vector>

class CombatEntity {
  public:
    // vars
    Rectangle pos;
    std::vector<Attack> attacks;

    // funcs
    virtual void damageCalc(int damage, AttackElement attack);
    virtual void draw();
    virtual void drawEnergyBar();
    virtual void drawHealthBar();
    virtual void performAttack();
    virtual void takeDamage(int damage);
    virtual void update();
    virtual void updateCurrentTextureFrame();

    virtual void setCurrentTexture() = 0;

  private:
    int currentHealth;
    int currentEnergy;
    int maxHealth;
    int maxEnergy;
};
