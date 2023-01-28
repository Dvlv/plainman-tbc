#pragma once

#include "attack.h"
#include "cast-effect.h"
#include "damage-bubble.h"
#include "enemy.h"
#include "player.h"
#include "ui.h"
#include <vector>

class CombatState {
private:
  Player *player;

  PlayerAttackMenu *playerAtkMenu;

  PlayerCombatData playerCombatData;

  int selectedEnemy;
  bool performingAttack;
  bool animationPlaying;
  bool doAttack;
  bool isPlayerTurn;
  bool playerWon;
  bool playerLost;

  int currentlyAttackingEnemy;
  bool isEnemyAttacking;

  std::vector<Attack> allAttacks;
  std::vector<Enemy *> enemies;
  std::vector<Rectangle> enemyPositions;
  std::vector<DamageBubble> damageBubbles;
  std::vector<CastEffect> castEffects;

public:
  CombatState(PlayerCombatData playerCombatData);

  void updatePlayerTurn();
  void updateEnemyTurn();

  const void postPlayerAttack();
  const void postEnemyAttack();

  bool shouldQuit;

  void update();
  void draw();

  ~CombatState();
};
