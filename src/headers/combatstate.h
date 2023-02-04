#pragma once

#include "attack.h"
#include "cast-effect.h"
#include "damage-bubble.h"
#include "enemy.h"
#include "player.h"
#include "ui.h"
#include <memory>
#include <vector>

class CombatState {
private:
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
  std::vector<std::shared_ptr<Enemy>> enemies;
  std::vector<Rectangle> enemyPositions;
  std::vector<DamageBubble> damageBubbles;
  std::vector<CastEffect> castEffects;

public:
  CombatState(PlayerCombatData playerCombatData, int roundNumber);

  bool shouldQuit;
  Player *player;

  void updatePlayerTurn();
  void updateEnemyTurn();

  const void postPlayerAttack();
  const void postEnemyAttack();
  void update();
  void draw();

  ~CombatState();
};
