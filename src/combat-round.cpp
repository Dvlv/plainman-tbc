#include "headers/combat-round.h"
#include "headers/bird.h"
#include "headers/enemy.h"
#include "headers/ghost.h"
#include "headers/turtle.h"
#include "headers/utils.h"
#include "raylib.h"
#include <array>
#include <memory>
#include <random>

CombatRound::CombatRound(int roundNumber) {
  this->roundNumber = roundNumber;
  this->roundEnemies = std::vector<std::shared_ptr<Enemy>>();
}

std::vector<std::shared_ptr<Enemy>> *
CombatRound::getRoundEnemies(std::vector<Rectangle> *enemyPositions) {
  const int birdsRound = 2;
  const int ghostsRound = 5;

  const int earlyRoundBoundary = 5;
  const int midRoundBoundary = 10;
  const int lateRoundBoundary = 15;

  this->roundEnemies = std::vector<std::shared_ptr<Enemy>>();

  // get a random number of enemies, weighted towards 1 in early rounds and
  // toward 3 in later
  std::array<int, 6> weights;
  if (this->roundNumber < earlyRoundBoundary) {
    weights = {1, 1, 1, 1, 1, 2};
  } else if (this->roundNumber >= lateRoundBoundary) {
    weights = {1, 2, 2, 3, 3, 3};
  } else {
    weights = {1, 1, 1, 2, 2, 3};
  }

  int numEnemies = weights.at(randomChoice(6));
  if (this->roundNumber < 2) {
    // 2 enemies on round 1 is pain
    numEnemies = 1;
  }

  std::vector<std::string> enemyTypes = {"turtle"};

  if (this->roundNumber >= birdsRound) {
    enemyTypes.push_back("bird");
  }

  if (this->roundNumber >= ghostsRound) {
    enemyTypes.push_back("ghost");
  }

  // prevent 2 birds before lateRoundBoundary
  // also prevents 2 ghosts or bird/ghost combo
  bool restShouldBeWeaker = false;

  for (int i = 0; i < numEnemies; i++) {
    std::string enemyType = enemyTypes.at(randomChoice(enemyTypes.size()));
    int numStrongEnemies = 0;

    if (restShouldBeWeaker) {
      enemyType = "turtle";
    }

    // if we are in an early round, don't allow 2 tough enemies
    if (this->roundNumber < midRoundBoundary) {
      if (enemyType == "bird" || enemyType == "ghost") {
        if (!restShouldBeWeaker) {
          restShouldBeWeaker = true;
        }
      }
    } else if (this->roundNumber < lateRoundBoundary) {
      // if we are in a mid round, don't allow 3 tough enemies
      if (enemyType == "bird" || enemyType == "ghost") {
        if (numStrongEnemies > 1) {
          enemyType = "turtle";
        }
      }
    }

    if (enemyType != "turtle") {
      numStrongEnemies++;
    }

    if (enemyType == "turtle") {
      this->roundEnemies.push_back(
          std::make_shared<Turtle>(enemyPositions->at(i), this->roundNumber));
    } else if (enemyType == "bird") {
      this->roundEnemies.push_back(
          std::make_shared<Bird>(enemyPositions->at(i)));
    } else if (enemyType == "ghost") {
      this->roundEnemies.push_back(
          std::make_shared<Ghost>(enemyPositions->at(i)));
    }
  }

  return &this->roundEnemies;
}
