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
  this->isPlayerTurn = true;

  this->player = new Player(Rectangle{350, 350, 100, 100}, 10, 5);
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
  Enemy turtle = Enemy("Turtle", 1, 1, 1, enAtks);
  Enemy turtle2 = Enemy("Turtle", 1, 1, 1, enAtks);

  this->enemies = std::vector<Enemy>{turtle, turtle2};
}

void GameState::updatePlayerTurn() {
  // Player Performing Attack
  if (this->performingAttack) {
    if (this->animationPlaying) {
      // No logic, wait for animations to draw
      return;
    }

    Attack *selectedAttack = &this->player->getAttacks()->at(
        this->playerAtkMenu->getHighlightedAttack());

    this->enemies[this->selectedEnemy].takeDamage(selectedAttack->damage);

    this->performingAttack = false;
    this->isPlayerTurn = false;
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
      // change attack
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
      int selectedAttackIdx = this->playerAtkMenu->getHighlightedAttack();
      Attack *selectedAttack =
          &this->player->getAttacks()->at(selectedAttackIdx);

      Rectangle selectedEnemyBounds = this->enemyPositions[this->selectedEnemy];

      this->animationPlaying = true;
      this->player->performAttack(selectedAttack, selectedEnemyBounds,
                                  &this->animationPlaying);
    }
  }
}

void GameState::updateEnemyTurn() {}

void GameState::update() {
  if (this->isPlayerTurn) {
    updatePlayerTurn();
    this->player->update();
  } else {
    updateEnemyTurn();

    for (auto &e : this->enemies) {
      e.update();
    }
  }
}

void GameState::draw() {
  // TODO calculate positions for player and enemy
  this->player->draw();

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

  drawPlayerAttackMenu(this->playerAtkMenu);
}
