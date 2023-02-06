#pragma once

#include "attack.h"
#include "enemy.h"
#include "player.h"
#include <memory>
#include <vector>

class PlayerAttackMenu {
public:
  PlayerAttackMenu(std::shared_ptr<Player> player);
  std::shared_ptr<Player> player;

  int highlightedOption;
  bool attackSelected;
  void changeHighlighted(int dir);
  void selectAttack();
  int getHighlightedAttack();
  std::shared_ptr<std::vector<Attack>> getPlayerAttacks();
};

void drawArrowOverEnemy(Rectangle pos);
void drawDamageHit(Rectangle pos, int dmg);
void drawCastEffect(Rectangle pos);

void drawPlayerAttackMenu(std::shared_ptr<PlayerAttackMenu> pam,
                          std::shared_ptr<Enemy> enemy = nullptr);

void drawPlayerStats(std::shared_ptr<Player> player);
void drawEnemyStats(std::shared_ptr<Enemy> enemy);
