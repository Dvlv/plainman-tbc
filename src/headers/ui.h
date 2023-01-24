#pragma once

#include "attack.h"
#include "enemy.h"
#include "player.h"
#include <vector>

class PlayerAttackMenu {
private:
  int highlightedOption;

public:
  PlayerAttackMenu(Player *player);
  Player *player;

  bool attackSelected;
  void changeHighlighted(int dir);
  void selectAttack();
  int getHighlightedAttack();
  std::vector<Attack> *getPlayerAttacks();
};

void drawArrowOverEnemy(Rectangle pos);
void drawDamageHit(Rectangle pos, int dmg);

void drawPlayerAttackMenu(PlayerAttackMenu *pam, Enemy *enemy = nullptr);

void drawPlayerStats(Player *player);
void drawEnemyStats(Enemy *enemy);
