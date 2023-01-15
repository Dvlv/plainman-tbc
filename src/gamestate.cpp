#include "headers/gamestate.h"
#include "headers/attack.h"
#include "headers/enemy.h"
#include "headers/player.h"
#include "headers/ui.h"
#include "raylib.h"
#include <vector>

GameState::GameState() {
  // state management
  this->selectedEnemy = 0;
  this->performingAttack = false;

  this->player = new Player(10, 5);
  this->playerAtkMenu = new PlayerAttackMenu(this->player);

  this->enemyPositions = std::vector<Rectangle>{Rectangle{750, 350, 100, 100},
                                                Rectangle{900, 350, 100, 100}};

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
  Enemy turtle2 = Enemy("Turtle", 5, 1, 1, enAtks);

  this->enemies = std::vector<Enemy>{turtle, turtle2};
}

void GameState::update() {
  if (this->performingAttack) {
    if (this->animationsPlaying) {
      // No logic, wait for animations to draw
      return;
    }
  }

  // select attack
  if (!this->playerAtkMenu->attackSelected) {
    if (IsKeyPressed(KEY_RIGHT)) {
      this->playerAtkMenu->changeHighlighted(1);
    } else if (IsKeyPressed(KEY_LEFT)) {
      this->playerAtkMenu->changeHighlighted(-1);
    }

    if (IsKeyPressed(KEY_ENTER)) {
      this->playerAtkMenu->attackSelected = true;
    }

  } else {
    // select enemy or change attack
    if (IsKeyPressed(KEY_BACKSPACE)) {
      this->playerAtkMenu->attackSelected = false;
    } else if (IsKeyPressed(KEY_RIGHT)) {
      this->selectedEnemy += 1;

      if (this->selectedEnemy >= this->enemies.size()) {
        this->selectedEnemy = this->enemies.size() - 1;
      }

    } else if (IsKeyPressed(KEY_LEFT)) {
      this->selectedEnemy -= 1;

      if (this->selectedEnemy < 0) {
        this->selectedEnemy = 0;
      }

    } else if (IsKeyPressed(KEY_ENTER)) {
      // choose enemy and perform attack
      this->performingAttack = true;
      // TODO tell player to play atk animation
      int selectedAttackIdx = this->playerAtkMenu->getHighlightedAttack();
      Attack *selectedAttack =
          &this->player->getAttacks()->at(selectedAttackIdx);

      this->animationsPlaying = true;
      this->player->performAttack(selectedAttack, &this->animationsPlaying);
      // TODO swap state to "enemy turn"
    }
  }
}

void GameState::draw() {
  // TODO calculate positions for player and enemy
  Rectangle playerPos = Rectangle{350, 350, 100, 100};

  this->player->draw(playerPos);

  int idx = 0;
  for (auto &e : this->enemies) {
    if (idx >= this->enemyPositions.size()) {
      // more enemies than available positions
      break;
    }

    e.draw(this->enemyPositions[idx]);

    // if player selecting enemy to attack, draw arrow
    if (this->playerAtkMenu->attackSelected) {
      if (idx == this->selectedEnemy) {
        drawArrowOverEnemy(this->enemyPositions[idx]);
      }
    }

    idx++;
  }

  // TODO state, player or enemy turn etc.

  drawPlayerAttackMenu(this->playerAtkMenu);
}
