#include "headers/ui.h"
#include "headers/enemy.h"
#include "raylib.h"
#include <vector>

// window is 1200 x 800

PlayerAttackMenu::PlayerAttackMenu(Player *player) {
  this->player = player;
  this->highlightedOption = 0;
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

std::vector<Attack> *PlayerAttackMenu::getPlayerAttacks() {
  return this->player->getAttacks();
}

void drawArrowOverEnemy(Rectangle pos) {
  const int indicatorHeight = 30;
  const int gap = 15;

  Vector2 topLeft = Vector2{pos.x, pos.y - indicatorHeight - gap};
  Vector2 topRight = Vector2{pos.x + pos.width, pos.y - indicatorHeight - gap};
  Vector2 bottom = Vector2{pos.x + (pos.width / 2), pos.y - gap};

  DrawTriangle(topLeft, topRight, bottom, DARKGRAY);
}

void drawPlayerAttackMenu(PlayerAttackMenu *pam) {
  const int gap = 50;
  const int topX = 100;
  const int topY = GetScreenHeight() - gap - 200;
  const int atkMenuWidth = GetScreenWidth() - (topX * 2);

  Rectangle pos = Rectangle{topX, (float)topY, (float)atkMenuWidth, 200};
  DrawRectangleRec(pos, BEIGE);

  int nextTextPosY = topY + gap;
  int nextTextPosX = topX + gap;

  int idx = 0;
  for (Attack &atk : *pam->getPlayerAttacks()) {
    DrawText(atk.name.c_str(), nextTextPosX, nextTextPosY, 20, BLACK);

    int textWidth = MeasureText(atk.name.c_str(), 20);

    if (idx == pam->getHighlightedAttack()) {
      DrawRectangleLines(nextTextPosX - 5, nextTextPosY - 5, textWidth + 10, 30,
                         DARKGRAY);
    }

    nextTextPosX += textWidth + gap;
    idx++;
  }
}

void drawPlayerStats(Player *player) {}
void drawEnemyStats(Enemy *enemy) {}
