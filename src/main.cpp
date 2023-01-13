#include "raylib.h"

#include "headers/gamestate.h"

void init();
void update();
void draw();

GameState *gs = new GameState();

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

  gs->draw();

  EndDrawing();
}

void update() { gs->update(); }

void init() {
  SetTargetFPS(60);

  InitWindow(1200, 800, "PlainMan");
}
