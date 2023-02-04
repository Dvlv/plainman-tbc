#pragma once

#include "attack.h"
#include "enemy.h"
#include "player.h"
#include <memory>
#include <vector>

class PlayerAttackMenu {
public:
  PlayerAttackMenu(Player *player);
  Player *player;

  int highlightedOption;
  bool attackSelected;
  void changeHighlighted(int dir);
  void selectAttack();
  int getHighlightedAttack();
  std::vector<Attack> *getPlayerAttacks();
};

void drawArrowOverEnemy(Rectangle pos);
void drawDamageHit(Rectangle pos, int dmg);
void drawCastEffect(Rectangle pos);

void drawPlayerAttackMenu(PlayerAttackMenu *pam,
                          std::shared_ptr<Enemy> enemy = nullptr);

void drawPlayerStats(Player *player);
void drawEnemyStats(Enemy *enemy);
