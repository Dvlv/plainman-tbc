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
    Attack("Punch", "A plain punch.", AttackType::PUNCH, 1, 0),
    Attack("Kick", "A plain kick.", AttackType::KICK, 1, 0),
    Attack("Shout", "A plain shout. \n1 Energy", AttackType::SHOUT, 2, 1),
};

bool isCombatState = false;

PlayerCombatData *playerCombatData = new PlayerCombatData{5, 5, &playerAttacks};
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
      levelsComplete++;

      delete cs;
      cs = new CombatState(*playerCombatData);

      isCombatState = false;
    }
  } else {
    sts->update();

    if (sts->isFinished) {
      isCombatState = true;
      sts->isFinished = false;
    }
  }
}

void init() {
  SetTargetFPS(60);

  InitWindow(1200, 800, "PlainMan");
}
