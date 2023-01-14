#pragma once

#include "attack.h"
#include "enemy.h"
#include "player.h"
#include "ui.h"
#include <vector>

class GameState {
private:
  Player *player;
  std::vector<Attack> allAttacks;
  std::vector<Enemy> enemies;
  PlayerAttackMenu *playerAtkMenu;

public:
  GameState();
  void update();
  void draw();
};
