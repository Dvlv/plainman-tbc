#include "raylib.h"

#include "headers/combatstate.h"
#include "headers/player.h"
#include "headers/skilltree-state.h"
#include <vector>

void init();
void update();
void draw();

int levelsComplete = 0;

std::vector<Attack> playerAttacks{
    Attack("Punch", "A plain punch.\n1 Damage", AttackType::PUNCH, 1, 0),
    Attack("Shout", "A plain shout.\n1 Damage\n1 Energy", AttackType::SHOUT, 1,
           1),
};

bool isCombatState = false;

PlayerCombatData *playerCombatData =
    new PlayerCombatData{5, 5, &playerAttacks, 0};
CombatState *cs = new CombatState(*playerCombatData);
SkillTreeState *sts = new SkillTreeState(); // TODO

int main() {
  init();

  while (!WindowShouldClose()) {
    update();
    draw();
  }

  CloseWindow();

  return 0;
}

void draw() {
  BeginDrawing();

  if (isCombatState) {
    ClearBackground(GREEN);
    cs->draw();
  } else {
    ClearBackground(BROWN);
    sts->draw();
  }

  EndDrawing();
}

void update() {
  if (isCombatState) {
    if (!cs->shouldQuit) {
      cs->update();
    } else {
      playerCombatData->skillPoints++;
      levelsComplete++;

      // TODO make this a choice, requires new state I guess
      if (levelsComplete > 2 && levelsComplete % 3 == 0) {
        playerCombatData->maxHealth++;
        playerCombatData->maxEnergy++;
      }

      delete cs;
      cs = new CombatState(*playerCombatData);

      isCombatState = false;
    }
  } else {
    sts->playerSkillPoints = playerCombatData->skillPoints;
    sts->update();

    if (sts->isFinished) {
      isCombatState = true;
      sts->isFinished = false;

      if (sts->selectedAttack != nullptr) {
        playerCombatData->attacks->push_back(*sts->selectedAttack);
        playerCombatData->skillPoints -= sts->selectedAttackSkillPointCost;

        sts->selectedAttackSkillPointCost = 0;
        sts->selectedAttack = nullptr;
      }
    }
  }
}

void init() {
  SetTargetFPS(60);

  InitWindow(1200, 800, "PlainMan");
}
