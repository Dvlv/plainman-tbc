#include "headers/upgrade-state.h"
#include "raylib.h"

#include "headers/combatstate.h"
#include "headers/player.h"
#include "headers/skilltree-state.h"
#include <memory>
#include <vector>

enum class GameState {
  COMBAT,
  SKILLTREE,
  UPGRADE,
};

void init();
void update();
void draw();

int levelsComplete = 0;

std::vector<Attack> playerAttacks{
    Attack("Punch", "A plain punch.\n1 Damage", AttackType::PUNCH, 1, 0),
    Attack("Shout", "A plain shout.\n1 Damage\n1 Energy", AttackType::SHOUT, 1,
           1),
};

GameState gs = GameState::SKILLTREE;

std::shared_ptr<PlayerCombatData> playerCombatData =
    std::make_shared<PlayerCombatData>(PlayerCombatData{
        5, 3, 5, 3, std::make_shared<std::vector<Attack>>(playerAttacks), 0});

std::unique_ptr<CombatState> cs =
    std::make_unique<CombatState>(playerCombatData, levelsComplete);

std::unique_ptr<SkillTreeState> sts = std::make_unique<SkillTreeState>();

std::unique_ptr<UpgradeState> us = std::make_unique<UpgradeState>();

// transitions between states
bool playingTransition = false;
bool stateEnding = true; // controls direction of wipe
int transitionFrameCount = 0;
const int transitionFrameMax = 20; // half a second each one

int main() {
  init();

  while (!WindowShouldClose()) {
    update();
    draw();
  }

  if (gs == GameState::COMBAT) {
    // avoids segfault if game closed during combat
    cs.reset();
  }

  CloseWindow();

  return 0;
}

void draw() {
  BeginDrawing();

  if (playingTransition && stateEnding) {
    float mult = ((float)transitionFrameCount / (float)transitionFrameMax);
    DrawRectangle(0, 0, GetScreenWidth() * mult, GetScreenHeight(), BLACK);
    EndDrawing();

    return;
  }

  if (gs == GameState::COMBAT) {
    ClearBackground(GREEN);
    cs->draw();
  } else if (gs == GameState::SKILLTREE) {
    ClearBackground(BROWN);
    sts->draw();
  } else if (gs == GameState::UPGRADE) {
    ClearBackground(DARKBLUE);
    us->draw();
  }

  if (playingTransition && !stateEnding) {
    float mult = ((float)transitionFrameCount / (float)transitionFrameMax);
    float x = GetScreenWidth() * mult;
    int xint = (int)x;
    int width = (int)(GetScreenWidth() - x);

    DrawRectangle(xint, 0, width, GetScreenHeight(), BLACK);
  }
  EndDrawing();
}

void update() {
  if (playingTransition) {
    transitionFrameCount++;

    if (transitionFrameCount >= transitionFrameMax) {
      if (stateEnding) {
        transitionFrameCount = 0;
        stateEnding = !stateEnding;
      } else {
        playingTransition = false;
        transitionFrameCount = 0;
        stateEnding = !stateEnding;
      }
    }

    return;
  }

  if (gs == GameState::COMBAT) {
    if (!cs->shouldQuit) {
      cs->update();
    } else {
      playerCombatData->skillPoints++;
      levelsComplete++;

      // restore 50% of hp and energy
      playerCombatData->currentHealth =
          cs->player->currentHealth + (playerCombatData->maxHealth / 2);

      if (playerCombatData->currentHealth > playerCombatData->maxHealth) {
        playerCombatData->currentHealth = playerCombatData->maxHealth;
      }

      playerCombatData->currentEnergy =
          cs->player->currentEnergy + (playerCombatData->maxEnergy / 2);

      if (playerCombatData->currentEnergy > playerCombatData->maxEnergy) {
        playerCombatData->currentEnergy = playerCombatData->maxEnergy;
      }

      cs.reset();

      if (levelsComplete > 2 && levelsComplete % 3 == 0) {
        gs = GameState::UPGRADE;
      } else {
        gs = GameState::SKILLTREE;
      }
      playingTransition = true;
    }
  } else if (gs == GameState::SKILLTREE) {
    sts->playerSkillPoints = playerCombatData->skillPoints;
    sts->update();

    if (sts->isFinished) {
      cs = std::make_unique<CombatState>(playerCombatData, levelsComplete);

      sts->isFinished = false;

      if (sts->selectedAttack != nullptr) {
        playerCombatData->attacks->push_back(*sts->selectedAttack);
        playerCombatData->skillPoints -= sts->selectedAttackSkillPointCost;

        sts->selectedAttackSkillPointCost = 0;
        sts->selectedAttack = nullptr;
      }

      gs = GameState::COMBAT;
      playingTransition = true;
    }
  } else if (gs == GameState::UPGRADE) {
    us->update();

    if (us->shouldQuit) {
      switch (us->chosenUpgrade) {
      case ChosenUpgrade::HEALTH:
        playerCombatData->maxHealth += 2;
        playerCombatData->currentHealth += 1;
        break;
      case ChosenUpgrade::ENERGY:
        playerCombatData->maxEnergy += 2;
        playerCombatData->currentEnergy += 1;
        break;
      case ChosenUpgrade::BOTH:
        playerCombatData->maxHealth += 1;
        playerCombatData->maxEnergy += 1;
        break;
      default:
        break;
      }

      us->shouldQuit = false;

      cs = std::make_unique<CombatState>(playerCombatData, levelsComplete);

      gs = GameState::COMBAT;
      playingTransition = true;
    }
  }
}

void init() {
  SetTargetFPS(60);

  InitWindow(1200, 800, "PlainMan");
}
