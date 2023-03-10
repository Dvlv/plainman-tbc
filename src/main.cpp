#include "headers/upgrade-state.h"
#include "raylib.h"

#include "headers/combatstate.h"
#include "headers/menu-state.h"
#include "headers/player.h"
#include "headers/skilltree-state.h"
#include <memory>
#include <vector>

enum class GameState {
  COMBAT,
  SKILLTREE,
  UPGRADE,
  MAIN_MENU,
};

void init();
void update();
void draw();
void resetGame();

int levelsComplete = 0;
int deaths = 0;

std::vector<Attack> playerAttacks{
    Attack("Punch", "A plain punch.\n1 Damage", AttackType::PUNCH, 1, 0),
    Attack("Shout", "A plain shout.\n1 Damage\n1 Energy", AttackType::SHOUT, 1,
           1),
};

GameState gs = GameState::MAIN_MENU;

std::shared_ptr<PlayerCombatData> playerCombatData =
    std::make_shared<PlayerCombatData>(PlayerCombatData{
        5, 3, 5, 3, std::make_shared<std::vector<Attack>>(playerAttacks), 0});

std::unique_ptr<CombatState> cs =
    std::make_unique<CombatState>(playerCombatData, levelsComplete);

std::unique_ptr<SkillTreeState> sts = std::make_unique<SkillTreeState>();

std::unique_ptr<UpgradeState> us = std::make_unique<UpgradeState>();

std::unique_ptr<MenuState> ms = std::make_unique<MenuState>();

// transitions between states
bool playingTransition = false;
bool stateEnding = true; // controls direction of wipe
int transitionFrameCount = 0;
const int transitionFrameMax = 20; // half a second each one

// Load BGs
bool texturesLoaded = false;
Texture2D combatBG;

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

  UnloadTexture(combatBG);
  CloseWindow();

  return 0;
}

void draw() {
  if (!texturesLoaded) {
    combatBG = LoadTexture("src/assets/art/combat/combat-bg-1.png");
    texturesLoaded = true;
  }

  BeginDrawing();

  if (playingTransition && stateEnding) {
    float mult = ((float)transitionFrameCount / (float)transitionFrameMax);
    DrawRectangle(0, 0, GetScreenWidth() * mult, GetScreenHeight(), BLACK);
    EndDrawing();

    return;
  }

  if (gs == GameState::COMBAT) {
    ClearBackground(GREEN);

    DrawTexture(combatBG, 0, 0, WHITE);

    cs->draw();
  } else if (gs == GameState::SKILLTREE) {
    ClearBackground(BROWN);
    sts->draw();
  } else if (gs == GameState::UPGRADE) {
    ClearBackground(DARKBLUE);
    us->draw();
  } else if (gs == GameState::MAIN_MENU) {
    ClearBackground(LIGHTGRAY);
    ms->draw();
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
      if (cs->playerLost) {
        deaths++;
        if (deaths > 1) {
          // lose entirely, reset
          resetGame();
          return;
        }
      } else {
        levelsComplete++;
      }
      playerCombatData->skillPoints++;

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

      if (levelsComplete > 1 && levelsComplete % 2 == 0) {
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
        playerCombatData->maxHealth += 3;
        playerCombatData->currentHealth = playerCombatData->maxHealth;
        break;
      case ChosenUpgrade::ENERGY:
        playerCombatData->maxEnergy += 3;
        playerCombatData->currentEnergy = playerCombatData->maxEnergy;
        break;
      case ChosenUpgrade::BOTH:
        playerCombatData->maxHealth += 2;
        playerCombatData->maxEnergy += 1;

        playerCombatData->currentHealth += 2;
        playerCombatData->currentEnergy += 2;

        if (playerCombatData->currentHealth > playerCombatData->maxHealth) {
          playerCombatData->currentHealth = playerCombatData->maxHealth;
        }
        if (playerCombatData->currentEnergy > playerCombatData->maxEnergy) {
          playerCombatData->currentEnergy = playerCombatData->maxEnergy;
        }

        break;
      default:
        break;
      }

      us->shouldQuit = false;

      cs = std::make_unique<CombatState>(playerCombatData, levelsComplete);

      gs = GameState::COMBAT;
      playingTransition = true;
    }
  } else if (gs == GameState::MAIN_MENU) {
    ms->update();

    if (ms->isFinished) {
      ms->isFinished = false;

      gs = GameState::SKILLTREE;
      playingTransition = true;
    }
  }
}

void resetGame() {
  // reset all variables which track progress to the
  // same as they are at the top  of this file
  // TODO draw something saying they lose 5ever and back to main menu

  levelsComplete = 0;
  deaths = 0;

  playerAttacks = {
      Attack("Punch", "A plain punch.\n1 Damage", AttackType::PUNCH, 1, 0),
      Attack("Shout", "A plain shout.\n1 Damage\n1 Energy", AttackType::SHOUT,
             1, 1),
  };

  gs = GameState::MAIN_MENU;

  playerCombatData = std::make_shared<PlayerCombatData>(PlayerCombatData{
      5, 3, 5, 3, std::make_shared<std::vector<Attack>>(playerAttacks), 0});

  cs = std::make_unique<CombatState>(playerCombatData, levelsComplete);

  sts = std::make_unique<SkillTreeState>();

  us = std::make_unique<UpgradeState>();

  ms = std::make_unique<MenuState>();
}

void init() {
  SetTargetFPS(60);

  InitWindow(1200, 800, "PlainMan");
}
