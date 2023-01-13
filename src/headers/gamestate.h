#pragma once

#include "attack.h"
#include "player.h"
#include "ui.h"
#include <vector>

class GameState {
private:
  Player *player;
  std::vector<Attack> allAttacks;

public:
  GameState();
  void update();
  void draw();
};
