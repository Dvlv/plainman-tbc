#include "headers/upgrade-state.h"
#include "raylib.h"

UpgradeState::UpgradeState() {
  this->highlightedOption = 0;
  this->shouldQuit = false;
}

void UpgradeState::draw() {
  const int gap = 50;
  int boxWidth = (int)(GetScreenWidth() / 3) - (gap * 1.5);
  int boxHeight = GetScreenHeight() - (gap * 2);
  int boxY = gap;

  // draw box around selected
  int selectedPos =
      gap * (this->highlightedOption + 1) + boxWidth * this->highlightedOption;
  DrawRectangle(selectedPos - 5, boxY - 5, boxWidth + 10, boxHeight + 10,
                SKYBLUE);

  // draw the boxes
  // HP
  DrawRectangle(gap, boxY, boxWidth, boxHeight, BEIGE);
  int textWHp = MeasureText("+2 HP", 30);
  int textXHp = gap + (boxWidth / 2) - (textWHp / 2);
  DrawText("+2 HP", textXHp, boxY + (boxHeight / 2) - 15, 30, BLACK);

  // Energy
  DrawRectangle(boxWidth + gap * 2, boxY, boxWidth, boxHeight, BEIGE);
  int textWEnergy = MeasureText("+2 Energy", 30);
  int textXEnerg = boxWidth + gap * 2 + (boxWidth / 2) - (textWEnergy / 2);
  DrawText("+2 Energy", textXEnerg, boxY + (boxHeight / 2) - 15, 30, BLACK);

  // Both
  DrawRectangle(boxWidth * 2 + gap * 3, boxY, boxWidth, boxHeight, BEIGE);
  int textWBoth = MeasureText("+1 HP +1 Energy", 30);
  int textXBoth = boxWidth * 2 + gap * 3 + (boxWidth / 2) - (textWBoth / 2);
  DrawText("+1 HP +1 Energy", textXBoth, boxY + (boxHeight / 2) - 15, 30,
           BLACK);
}

void UpgradeState::update() {
  if (IsKeyPressed(KEY_RIGHT)) {
    this->highlightedOption++;
    if (this->highlightedOption > 2) {
      this->highlightedOption = 2;
    }
  } else if (IsKeyPressed(KEY_LEFT)) {
    this->highlightedOption--;
    if (this->highlightedOption < 0) {
      this->highlightedOption = 0;
    }
  }

  if (IsKeyPressed(KEY_ENTER)) {
    if (this->highlightedOption == 0) {
      this->chosenUpgrade = ChosenUpgrade::HEALTH;
    } else if (this->highlightedOption == 1) {
      this->chosenUpgrade = ChosenUpgrade::ENERGY;
    } else if (this->highlightedOption == 2) {
      this->chosenUpgrade = ChosenUpgrade::BOTH;
    }
    this->shouldQuit = true;
  }
}
