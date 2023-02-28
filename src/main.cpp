#include "headers/combat-state.h"
#include "headers/enums.h"
#include "raylib.h"
#include <iostream>
#include <memory>

using std::make_unique;
using std::unique_ptr;

using std::make_shared;
using std::shared_ptr;

// global vars
static unique_ptr<CombatState> cs = make_unique<CombatState>();
static GameState gs = GameState::COMBAT;

void init();
void update();
void draw();

int main() {
    init();

    while (!WindowShouldClose()) {
        update();
        draw();
    }

    CloseWindow();

    return 0;
}

void init() {
    InitWindow(800, 600, "PlainMan");
    SetTargetFPS(60);
}

void draw() {
    BeginDrawing();
    switch (gs) {
    case GameState::COMBAT:
        ClearBackground(RAYWHITE);
        cs->draw();
        break;
    default:
        ClearBackground(RED);
        break;
    }
    EndDrawing();
}

void update() {}
