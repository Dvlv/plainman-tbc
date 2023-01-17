#pragma once

#include "attack.h"
#include "enemy.h"
#include "player.h"
#include "ui.h"
#include <vector>

class CombatState {
private:
  Player *player;

  PlayerAttackMenu *playerAtkMenu;

  int selectedEnemy;
  bool performingAttack;
  bool animationPlaying;
  bool isPlayerTurn;
  bool playerWon;
  bool playerLost;

  int currentlyAttackingEnemy;
  bool isEnemyAttacking;

  std::vector<Attack> allAttacks;
  std::vector<Enemy> enemies;
  std::vector<Rectangle> enemyPositions;

public:
  CombatState();

  void updatePlayerTurn();
  void updateEnemyTurn();

  bool shouldQuit;

  void update();
  void draw();
};
