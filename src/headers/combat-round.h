#pragma once

#include "bird.h"
#include "enemy.h"
#include "raylib.h"
#include "texture-store.h"
#include "turtle.h"
#include <memory>
#include <vector>

class CombatRound {
public:
  CombatRound(int roundNumber);

  // vars
  int roundNumber;
  std::vector<std::shared_ptr<Enemy>> roundEnemies;

  // funcs
  std::vector<std::shared_ptr<Enemy>> *
  getRoundEnemies(std::vector<Rectangle> *enemyPositions);

  ~CombatRound() = default;
};
