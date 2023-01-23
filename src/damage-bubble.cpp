#include "headers/damage-bubble.h"
#include "raylib.h"
#include <string>

DamageBubble::DamageBubble(Rectangle pos, int damageNumber) {
  this->pos = pos;
  this->damageNumber = damageNumber;
  this->lifetime = 30;
  this->currentFrameCount = 0;
  this->canBeDeleted = false;
}

void DamageBubble::update() {
  this->currentFrameCount++;

  if (this->currentFrameCount >= this->lifetime) {
    this->canBeDeleted = true;
  }

  this->pos.y -= 2;
}

void DamageBubble::draw() {
  Color bubbleColor = {255, 20, 20, 188};
  int textSize = MeasureText(std::to_string(this->damageNumber).c_str(), 20);

  DrawCircle(this->pos.x + this->pos.width / 2, this->pos.y, 20, bubbleColor);

  DrawText(std::to_string(this->damageNumber).c_str(),
           this->pos.x + (this->pos.width / 2) - (textSize / 2),
           this->pos.y - 10, 20, WHITE);
}
