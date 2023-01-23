#include "headers/combatstate.h"
#include "headers/attack.h"
#include "headers/bird.h"
#include "headers/enemy.h"
#include "headers/player.h"
#include "headers/turtle.h"
#include "headers/ui.h"
#include "raylib.h"
#include <vector>

CombatState::CombatState() {
  this->selectedEnemy = 0;
  this->performingAttack = false;
  this->isPlayerTurn = true;
  this->currentlyAttackingEnemy = -1; // this gets ++'d to 0 on updateEnemyTurn
  this->playerWon = false;
  this->playerLost = false;
  this->shouldQuit = false;

  this->player = new Player(Rectangle{350, 350, 100, 100}, 10, 5);
  this->playerAtkMenu = new PlayerAttackMenu(this->player);

  this->enemyPositions = std::vector<Rectangle>{Rectangle{750, 350, 100, 100},
                                                Rectangle{900, 350, 100, 100}};

  // TODO read these from a resource file
  Attack atkPunch = Attack("Punch", "A plain punch", AttackType::PUNCH, 1);
  Attack atkKick = Attack("Kick", "A plain kick", AttackType::KICK, 1);
  Attack atkShout = Attack("Shout", "A plain shout", AttackType::SHOUT, 1);

  player->addAttack(atkPunch);
  player->addAttack(atkKick);
  player->addAttack(atkShout);

  // TODO read these from a level file, or random gen
  Enemy turtle = Turtle(this->enemyPositions[0]);
  Enemy bird = Bird(this->enemyPositions[1]);

  this->enemies = std::vector<Enemy>{turtle, bird};
  this->damageBubbles = std::vector<DamageBubble>{};
}

void CombatState::updatePlayerTurn() {
  // Player Performing Attack
  if (this->performingAttack) {
    if (this->animationPlaying) {
      // No logic, wait for animations to draw
      return;
    }

    Attack *selectedAttack = &this->player->getAttacks()->at(
        this->playerAtkMenu->getHighlightedAttack());

    this->enemies[this->selectedEnemy].takeDamage(selectedAttack->damage);

    // spawn damage bubble
    Rectangle dmgBubblePos = this->enemies[this->selectedEnemy].pos;
    dmgBubblePos.y -= 30;
    this->damageBubbles.push_back(
        DamageBubble(dmgBubblePos, selectedAttack->damage));

    this->performingAttack = false;
    this->isPlayerTurn = false;
    this->playerAtkMenu->attackSelected = false;
  }

  // select attack
  if (!this->playerAtkMenu->attackSelected) {
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_DOWN)) {
      this->playerAtkMenu->changeHighlighted(1);
    } else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_UP)) {
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

      Rectangle selectedEnemyBounds = this->enemies[this->selectedEnemy].pos;

      this->animationPlaying = true;
      this->player->performAttack(selectedAttack, selectedEnemyBounds,
                                  &this->animationPlaying);
    }
  }
}

void CombatState::updateEnemyTurn() {
  // if all enemies are dead, return
  if (this->enemies.size() == 0) {
    this->playerWon = true;
    return;
  }

  if (this->isEnemyAttacking) {
    if (this->animationPlaying) {
      // no logic, wait for animation to play
      return;
    } else {
      // enemy attack animation is done, perform damage calcs and finish turn
      // TODO this and the player one both fetch twice
      Enemy *attackingEnemy = &this->enemies[this->currentlyAttackingEnemy];
      Attack *bestAtk = attackingEnemy->selectBestAttack();

      this->player->takeDamage(bestAtk->damage);

      // spawn damage bubble
      Rectangle dmgBubblePos = this->player->pos;
      dmgBubblePos.y -= 30;
      this->damageBubbles.push_back(
          DamageBubble(dmgBubblePos, bestAtk->damage));

      this->isEnemyAttacking = false;
      if (this->player->currentHealth <= 0) {
        this->playerLost = true;
      }
    }
  } else {
    // next enemy attacks, or if last enemy, back to player's turn
    this->currentlyAttackingEnemy++;

    if (this->currentlyAttackingEnemy >= this->enemies.size()) {
      // last enemy, player's turn
      this->currentlyAttackingEnemy = -1;
      this->isPlayerTurn = true;

      return;
    }

    // enemy chooses attack and performs animation
    this->isEnemyAttacking = true;
    this->animationPlaying = true;

    Enemy *attackingEnemy = &this->enemies[this->currentlyAttackingEnemy];
    Attack *bestAtk = attackingEnemy->selectBestAttack();
    attackingEnemy->performAttack(bestAtk, this->player->pos,
                                  &this->animationPlaying);
  }
}

void CombatState::update() {
  if (this->playerWon || this->playerLost) {
    if (IsKeyPressed(KEY_ENTER)) {
      this->shouldQuit = true;
      return;
    }
    return;
  }

  if (this->isPlayerTurn) {
    updatePlayerTurn();
    this->player->update();
  } else {
    // delete marked enemies
    std::vector<int> markedEnemies;

    for (int i = 0; i < this->enemies.size(); i++) {
      if (this->enemies[i].canBeDeleted) {
        markedEnemies.push_back(i);
      }
    }

    // if marked enemies, remove selectedEnemy
    if (markedEnemies.size() > 0) {
      this->selectedEnemy = 0;
      for (int i = 0; i < markedEnemies.size(); i++) {
        this->enemies.erase(this->enemies.begin() + markedEnemies[i]);
      }
    }

    updateEnemyTurn();
    this->player->update();
    for (auto &e : this->enemies) {
      e.update();
    }
  }

  // update damage bubbles
  int dbIdx = 0;
  for (auto &db : this->damageBubbles) {
    db.update();
    if (db.canBeDeleted) {
      // TODO filter this properly
      this->damageBubbles.erase(this->damageBubbles.begin());
    }
  }
}

void CombatState::draw() {
  if (this->playerWon) {
    DrawText("You won!", 400, 300, 40, BLACK);
    return;
  } else if (this->playerLost) {
    DrawText("You lost!", 400, 300, 40, BLACK);
    return;
  }
  // TODO calculate positions for player and enemy

  // Draw player on bottom if enemy's turn
  if (!this->isPlayerTurn) {
    this->player->draw();
  }

  int idx = 0;
  for (auto &e : this->enemies) {
    if (idx >= this->enemyPositions.size()) {
      // more enemies than available positions
      break;
    }

    e.draw();

    // if player selecting enemy to attack, draw arrow
    if (this->playerAtkMenu->attackSelected) {
      if (idx == this->selectedEnemy) {
        drawArrowOverEnemy(this->enemies[idx].pos);
      }
    }

    idx++;
  }

  // draw player on top if player's turn
  if (this->isPlayerTurn) {
    this->player->draw();
    // not performing attack, draw attack menu
    if (!this->performingAttack && !this->animationPlaying) {
      if (this->playerAtkMenu->attackSelected) {
        drawPlayerAttackMenu(this->playerAtkMenu,
                             &this->enemies.at(this->selectedEnemy));
      } else {
        drawPlayerAttackMenu(this->playerAtkMenu);
      }
    } else if (this->performingAttack && !this->animationPlaying) {
      // damage just performed, draw in UI
      Attack *selectedAttack = &this->player->getAttacks()->at(
          this->playerAtkMenu->getHighlightedAttack());

      // TODO this may need to be signalled by the player on their
      // MeleeAnimationState::BACK movement
      drawDamageHit(this->enemies.at(this->selectedEnemy).pos,
                    selectedAttack->damage);
    }
  }

  // draw any damage bubbles
  for (auto &db : this->damageBubbles) {
    db.draw();
  }
}

CombatState::~CombatState() {
  delete this->player;
  delete this->playerAtkMenu;
}
