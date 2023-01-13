#include "headers/gamestate.h"
#include "headers/attack.h"
#include "headers/player.h"
#include "raylib.h"

GameState::GameState() {
  this->player = new Player(10, 5);

  // TODO read these from a resource file
  Attack atkPunch = Attack("Punch", AttackType::PUNCH, 1);
  Attack atkKick = Attack("Kick", AttackType::KICK, 1);
  Attack atkShout = Attack("Shout", AttackType::SHOUT, 1);

  player->addAttack(atkPunch);
  player->addAttack(atkKick);
  player->addAttack(atkShout);
}

void GameState::update() {}

void GameState::draw() {
  // TODO calculate positions for player and enemy
  Rectangle playerPos = Rectangle{350, 350, 100, 100};

  this->player->draw(playerPos);
}
