#include "headers/ui.h"
#include "headers/enemy.h"
#include "raylib.h"
#include <memory>
#include <vector>

// window is 1200 x 800

PlayerAttackMenu::PlayerAttackMenu(std::shared_ptr<Player> player) {
  this->player = player;
  this->highlightedOption = 0;
  this->attackSelected = false;
}

void PlayerAttackMenu::changeHighlighted(int dir) {
  this->highlightedOption += dir;

  // clamp
  if (this->highlightedOption < 0) {
    this->highlightedOption = 0;
  } else if (this->highlightedOption >= this->getPlayerAttacks()->size()) {
    this->highlightedOption = this->getPlayerAttacks()->size() - 1;
  }
}

int PlayerAttackMenu::getHighlightedAttack() { return this->highlightedOption; }

void PlayerAttackMenu::selectAttack() { this->attackSelected = true; }

std::shared_ptr<std::vector<Attack>> PlayerAttackMenu::getPlayerAttacks() {
  return this->player->getAttacks();
}

void drawArrowOverEnemy(Rectangle pos) {
  const int indicatorHeight = 30;
  const int gap = 15;

  Vector2 topLeft = Vector2{pos.x + gap, pos.y - indicatorHeight - gap};
  Vector2 topRight =
      Vector2{pos.x + pos.width - gap, pos.y - indicatorHeight - gap};
  Vector2 bottom = Vector2{pos.x + (pos.width / 2), pos.y - gap};

  DrawTriangle(Vector2{topRight.x + 6, topRight.y - 3},
               Vector2{topLeft.x - 6, topLeft.y - 3},
               Vector2{bottom.x, bottom.y + 3}, DARKGRAY);
  DrawTriangle(topRight, topLeft, bottom, LIGHTGRAY);
}

void drawPlayerAttackMenu(std::shared_ptr<PlayerAttackMenu> pam,
                          std::shared_ptr<Enemy> enemy) {
  const int gap = 15;
  const int gapX = 25;
  const int topX = 100;
  const int topY = GetScreenHeight() - gap - 200;
  const int atkMenuWidth = GetScreenWidth() - (topX * 2);
  const int textHeight = 20;

  // description constants
  const int descX = topX + (atkMenuWidth * 0.65);
  const int descY = topY + textHeight;

  Rectangle pos = Rectangle{topX, (float)topY, (float)atkMenuWidth, 200};
  DrawRectangleRec(pos, BEIGE);

  int nextTextPosY = topY + gap;
  int nextTextPosX = topX + gapX;

  // Draw attack text
  const int maxAttacksPerColumn = 5; // actually shows 5, but 0 indexed
  const int attackTextWidth = 100;

  int idx = 0;
  int currentCol = 1;
  for (Attack &atk : *pam->getPlayerAttacks()) {
    bool hasEnergy = pam->player->currentEnergy >= atk.energyCost;

    Color textColor = hasEnergy ? BLACK : GRAY;

    DrawText(atk.name.c_str(), (nextTextPosX * currentCol), nextTextPosY,
             textHeight, textColor);

    int textWidth = MeasureText(atk.name.c_str(), textHeight);

    if (idx == pam->getHighlightedAttack()) {
      Color boxClr = pam->attackSelected ? RED : DARKGRAY;
      DrawRectangleLines((nextTextPosX * currentCol) - 5, nextTextPosY - 5,
                         textWidth + 10, 30, boxClr);
    }

    nextTextPosY += textHeight + gap;

    idx++;

    // when this could overflow, move to a second column
    int nextCol = (idx / maxAttacksPerColumn) + 1;
    if (nextCol > currentCol) {
      currentCol = nextCol;
      nextTextPosY = topY + gap;
    }
  }

  if (pam->attackSelected && enemy != nullptr) {
    // Attack selected so show description of enemy being targeted
    DrawText(enemy->description.c_str(), descX, descY, textHeight, BLACK);
  } else {
    // Draw description of move being hovered
    DrawText(pam->getPlayerAttacks()
                 ->at(pam->getHighlightedAttack())
                 .description.c_str(),
             descX, descY, textHeight, BLACK);
  }
}

void drawPlayerStats(std::shared_ptr<Player> player) {}
void drawEnemyStats(std::shared_ptr<Enemy> enemy) {}

void drawDamageHit(Rectangle pos, int dmg) {
  // printf("Enemy at %d %d takes %d damage\n", (int)pos.x, (int)pos.y, dmg);
}
