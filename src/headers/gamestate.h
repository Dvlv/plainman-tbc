#pragma once

#include "attack.h"
#include "enemy.h"
#include "player.h"
#include "ui.h"
#include <vector>

class GameState {
private:
  Player *player;

  PlayerAttackMenu *playerAtkMenu;

  int selectedEnemy;
  bool performingAttack;
  bool animationsPlaying;

  std::vector<Attack> allAttacks;
  std::vector<Enemy> enemies;
  std::vector<Rectangle> enemyPositions;

public:
  GameState();
  void update();
  void draw();
};
