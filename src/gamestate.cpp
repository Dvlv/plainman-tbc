#include "headers/gamestate.h"
#include "headers/attack.h"
#include "headers/enemy.h"
#include "headers/player.h"
#include "raylib.h"
#include <vector>

// TODO make this constructor
GameState::GameState() {
  this->player = new Player(10, 5);

  // TODO read these from a resource file
  Attack atkPunch = Attack("Punch", AttackType::PUNCH, 1);
  Attack atkKick = Attack("Kick", AttackType::KICK, 1);
  Attack atkShout = Attack("Shout", AttackType::SHOUT, 1);

  player->addAttack(atkPunch);
  player->addAttack(atkKick);
  player->addAttack(atkShout);

  // TODO read these from a level file, or random gen
  std::vector<Attack> enAtks{atkKick, atkShout};
  Enemy turtle = Enemy("Turtle", 5, 1, 1, enAtks);

  this->enemies = std::vector<Enemy>{turtle};
}

void GameState::update() {}

void GameState::draw() {
  // TODO calculate positions for player and enemy
  Rectangle playerPos = Rectangle{350, 350, 100, 100};

  this->player->draw(playerPos);

  Rectangle ePos = Rectangle{750, 350, 100, 100};
  for (auto &e : this->enemies) {
    e.draw(ePos);
  }

  // TODO state, player or enemy turn etc.

  // drawPlayerAttackMenu
}
