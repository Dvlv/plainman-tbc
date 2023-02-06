#include "headers/combat-round.h"
#include "headers/bird.h"
#include "headers/enemy.h"
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

  const int earlyRoundBoundary = 5;
  const int lateRoundBoundary = 10;

  this->roundEnemies = std::vector<std::shared_ptr<Enemy>>();

  // get a random number of enemies, weighted towards 1 in early rounds and
  // toward 3 in later
  std::array<int, 6> weights;
  if (this->roundNumber < earlyRoundBoundary) {
    weights = {1, 1, 1, 1, 1, 2};
  } else if (this->roundNumber >= lateRoundBoundary) {
    weights = {1, 2, 2, 3, 3, 3};
  } else {
    weights = {1, 1, 2, 2, 3, 3};
  }

  int numEnemies = weights.at(randomChoice(6));

  std::vector<std::string> enemyTypes = {"turtle"};

  if (this->roundNumber >= birdsRound) {
    enemyTypes.push_back("bird");
  }

  for (int i = 0; i < numEnemies; i++) {
    std::string enemyType = enemyTypes.at(randomChoice(enemyTypes.size()));

    // prevent 2 birds before lateRoundBoundary
    bool hasBird = false;

    if (enemyType == "bird") {
      if (!hasBird && roundNumber < lateRoundBoundary) {
        this->roundEnemies.push_back(
            std::make_shared<Bird>(enemyPositions->at(i)));

        hasBird = true;
      } else {
        // TODO when there's more than 2 enemy types, this can be i-- to
        // basically "re-roll"
        this->roundEnemies.push_back(
            std::make_shared<Turtle>(enemyPositions->at(i)));
      }
    } else if (enemyType == "turtle") {
      this->roundEnemies.push_back(
          std::make_shared<Turtle>(enemyPositions->at(i)));
    }
  }

  return &this->roundEnemies;
}
