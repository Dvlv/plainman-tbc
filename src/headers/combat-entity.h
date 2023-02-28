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
    virtual void damageCalc(int baseDamage, AttackElement attack);
    virtual void draw();
    virtual void drawEnergyBar();
    virtual void drawHealthBar();
    virtual void performAttack();
    virtual void takeDamage(int damage);
    virtual void updateCurrentTextureFrame();

    virtual void setCurrentTexture() = 0;
    virtual void update() = 0;

  protected:
    int currentHealth;
    int currentEnergy;
    int maxHealth;
    int maxEnergy;
};
