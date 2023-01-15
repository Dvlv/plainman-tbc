#pragma once

#include "attack.h"
#include "enemy.h"
#include "player.h"
#include <vector>

class PlayerAttackMenu {
private:
  Player *player;
  int highlightedOption;

public:
  bool attackSelected;
  PlayerAttackMenu(Player *player);
  void changeHighlighted(int dir);
  void selectAttack();
  int getHighlightedAttack();
  std::vector<Attack> *getPlayerAttacks();
};

void drawArrowOverEnemy(Rectangle pos);

void drawPlayerAttackMenu(PlayerAttackMenu *pam);

void drawPlayerStats(Player *player);
void drawEnemyStats(Enemy *enemy);