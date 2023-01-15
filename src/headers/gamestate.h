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
  bool animationPlaying;
  bool isPlayerTurn;

  std::vector<Attack> allAttacks;
  std::vector<Enemy> enemies;
  std::vector<Rectangle> enemyPositions;

public:
  GameState();

  void updatePlayerTurn();
  void updateEnemyTurn();

  void update();
  void draw();
};
