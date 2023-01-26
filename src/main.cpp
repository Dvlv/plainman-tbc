#include "raylib.h"

#include "headers/combatstate.h"
#include "headers/necromancer-skilltree.h"
#include "headers/player.h"
#include <vector>

void init();
void update();
void draw();

int levelsComplete = 0;

NecromancerSkilltree *nst = new NecromancerSkilltree();

std::vector<Attack> *currentAttackSkillTree = &nst->level1Attacks;

std::vector<Attack> playerAttacks{
    Attack("Punch", "A plain punch.", AttackType::PUNCH, 1, 0),
    Attack("Kick", "A plain kick.", AttackType::KICK, 1, 0),
    Attack("Shout", "A plain shout. \n1 Energy", AttackType::SHOUT, 2, 1),
};

PlayerCombatData *playerCombatData = new PlayerCombatData{5, 5, &playerAttacks};
CombatState *cs = new CombatState(*playerCombatData);

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

  ClearBackground(GREEN);

  cs->draw();

  EndDrawing();
}

void update() {
  if (!cs->shouldQuit) {
    cs->update();
  } else {
    // new game state
    // TODO go to map screen
    delete cs;

    Attack atk = currentAttackSkillTree->at(levelsComplete);
    playerAttacks.push_back(atk);
    levelsComplete++;

    // TODO some kind of pointer to the current level in the skill tree class
    if (levelsComplete > currentAttackSkillTree->size() - 1) {
      currentAttackSkillTree = &nst->level2Attacks;
      levelsComplete = 0;
    }

    cs = new CombatState(*playerCombatData);
  }
}

void init() {
  SetTargetFPS(60);

  InitWindow(1200, 800, "PlainMan");
}
