#include "headers/menu-state.h"
#include "raylib.h"

MenuState::MenuState() {
  this->isFinished = false;
  this->highlightedOption = 0;

  // Magic numbers:
  // 0 = Play
  // 1 = How to play
  // 2 = Credits
}

void MenuState::update() {
  if (IsKeyPressed(KEY_DOWN)) {
    this->highlightedOption++;

    if (this->highlightedOption > 2) {
      this->highlightedOption = 2;
    }
  }

  if (IsKeyPressed(KEY_UP)) {
    this->highlightedOption--;

    if (this->highlightedOption < 0) {
      this->highlightedOption = 0;
    }
  }

  if (IsKeyPressed(KEY_ENTER)) {
    this->chosenOption = this->highlightedOption;

    // 0 = Play
    if (this->chosenOption == 0) {
      this->isFinished = true;
    }

  } else if (IsKeyPressed(KEY_BACKSPACE)) {
    // chosen 0 means draw buttons again
    this->chosenOption = 0;
  }
}

void MenuState::draw() {
  int textWidth = MeasureText("PlainMan", 30);

  DrawText("PlainMan", GetScreenWidth() / 2 - textWidth / 2, 30, 30, BLACK);

  switch (this->chosenOption) {
  case 0:
    this->drawButtons();
    break;
  case 1:
    this->drawHowToPlay();
    break;
  case 2:
    this->drawCredits();
    break;
  }
}

void MenuState::drawHowToPlay() {

  int textWidth = MeasureText("How to Play", 20);

  DrawText("How to Play", GetScreenWidth() / 2 - textWidth / 2, 30 + 30 + 30,
           20, BLACK);
}

void MenuState::drawCredits() {

  int textWidth = MeasureText("Credits", 20);

  DrawText("Credits", GetScreenWidth() / 2 - textWidth / 2, 30 + 30 + 30, 20,
           BLACK);
}

void MenuState::drawButtons() {
  // draw selection
  DrawRectangle(100 - 10, 120 - 10 + (this->highlightedOption * 200),
                GetScreenWidth() - 180, 120, SKYBLUE);

  // Play
  DrawRectangle(100, 120, GetScreenWidth() - 200, 100, BEIGE);
  DrawText("Play", GetScreenWidth() / 2 - MeasureText("Play", 30) / 2,
           120 + (100 / 2) - 15, 30, BLACK);

  // How to play
  DrawRectangle(100, 320, GetScreenWidth() - 200, 100, BEIGE);
  DrawText("How to Play",
           GetScreenWidth() / 2 - MeasureText("How to Play", 30) / 2,
           320 + (100 / 2) - 15, 30, BLACK);
  // Credits
  DrawRectangle(100, 520, GetScreenWidth() - 200, 100, BEIGE);
  DrawText("Credits", GetScreenWidth() / 2 - MeasureText("Credits", 30) / 2,
           520 + (100 / 2) - 15, 30, BLACK);
}
