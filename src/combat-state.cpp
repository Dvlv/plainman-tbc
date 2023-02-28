#include "headers/combat-state.h"
#include "raylib.h"

CombatState::CombatState() {}

void CombatState::draw() { DrawText("Combat State", 100, 100, 20, BLACK); }
