#include "raylib.h"

#include "headers/combatstate.h"

void init();
void update();
void draw();

CombatState *cs = new CombatState();

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
    cs = new CombatState();
  }
}

void init() {
  SetTargetFPS(60);

  InitWindow(1200, 800, "PlainMan");
}
