#include "headers/heal-bubble.h"
#include "raylib.h"
#include <string>

HealBubble::HealBubble(Rectangle pos, int number, HealType type) {
  this->pos = pos;
  this->number = number;
  this->type = type;
  this->lifetime = 30;
  this->currentFrameCount = 0;
  this->canBeDeleted = false;
}

void HealBubble::update() {
  this->currentFrameCount++;

  if (this->currentFrameCount >= this->lifetime) {
    this->canBeDeleted = true;
  }

  this->pos.y -= 2;
}

void HealBubble::draw() {

  Color bubbleColor = DARKGREEN;
  if (this->type == HealType::ENERGY_BUBBLE) {
    // is a plus-energy bubble, draw as blue
    bubbleColor = DARKBLUE;
  }

  DrawCircle(this->pos.x + this->pos.width / 2, this->pos.y, 20, bubbleColor);

  std::string numberStr = std::to_string(this->number);

  int textSize = MeasureText(numberStr.c_str(), 20);

  DrawText(numberStr.c_str(),
           this->pos.x + (this->pos.width / 2) - (textSize / 2),
           this->pos.y - 10, 20, WHITE);
}
