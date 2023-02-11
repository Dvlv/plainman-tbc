#pragma once

#include "attack.h"
#include "cast-effect.h"
#include "damage-bubble.h"
#include "enemy.h"
#include "heal-bubble.h"
#include "player.h"
#include "texture-store.h"
#include "ui.h"
#include <map>
#include <memory>
#include <vector>

class CombatState {
private:
  std::shared_ptr<PlayerAttackMenu> playerAtkMenu;

  PlayerCombatData playerCombatData;

  int selectedEnemy;
  bool performingAttack;
  bool animationPlaying;
  bool doAttack;
  bool isPlayerTurn;
  bool playerWon;
  bool playerLost;
  int roundNumber;

  int currentlyAttackingEnemy;
  bool isEnemyAttacking;

  std::vector<Attack> allAttacks;
  std::vector<std::shared_ptr<Enemy>> enemies;
  std::vector<Rectangle> enemyPositions;
  std::vector<DamageBubble> damageBubbles;
  std::vector<HealBubble> healBubbles;
  std::vector<CastEffect> castEffects;

  bool hasCachedCastEffects = false;
  std::map<AttackElement, int> castEffectTexCache;

public:
  CombatState(std::shared_ptr<PlayerCombatData> playerCombatData,
              int roundNumber);

  bool shouldQuit;
  std::shared_ptr<Player> player;
  std::shared_ptr<TextureStore> textureStore;

  void cacheCastEffects();

  void updatePlayerTurn();
  void updateEnemyTurn();

  const void postPlayerAttack();
  const void postEnemyAttack();
  void update();
  void draw();

  ~CombatState();
};
