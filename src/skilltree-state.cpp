#include "headers/skilltree-state.h"
#include "headers/attack.h"
#include "headers/skilltree-node.h"
#include "headers/skilltree.h"
#include "raylib.h"
#include <vector>

SkillTreeState::SkillTreeState() {
  this->chosenSkillTree = nullptr;
  this->highlightedOption = 0;

  this->availableSkillTrees = std::vector<SkillTree>{
      SkillTree("Necromancer", "Summons Creatures to Attack",
                std::vector<SkillTreeNode>{SkillTreeNode(
                    new Attack("Skeleton", "Summon a Skeleton",
                               AttackType::SHOUT, 2, 2, AttackElement::FIRE),
                    1)}),
      SkillTree(
          "Assassin", "Uses status effects",
          std::vector<SkillTreeNode>{SkillTreeNode(
              new Attack("Poison", "Throws a vial of poison", AttackType::SHOUT,
                         2, 2, AttackElement::ELECTRIC),
              1)}),

  };
}

void SkillTreeState::chooseSkillTree(int skillTreeIndex) {
  this->chosenSkillTree = &this->availableSkillTrees[skillTreeIndex];
}

void SkillTreeState::drawTreePreview(int x, int y, int width, int height,
                                     SkillTree *tree, bool isHighlighted) {
  const int highlightWidth = 5;

  if (isHighlighted) {
    DrawRectangle(x - highlightWidth, y - highlightWidth,
                  width + highlightWidth * 2, height + highlightWidth * 2,
                  SKYBLUE);
  }

  DrawRectangle(x, y, width, height, BEIGE);

  // name
  DrawText(tree->className.c_str(), x + 10, y + 10, 30, BLACK);

  // description
  DrawText(tree->description.c_str(), x + 10, y + 50, 20, BLACK);
}

void SkillTreeState::update() {

  if (this->chosenSkillTree == nullptr) {
    // no skill tree chosen, listen for keyboard event to change
    // highlighted
    if (IsKeyPressed(KEY_RIGHT)) {
      this->highlightedOption++;
      if (this->highlightedOption >= this->availableSkillTrees.size()) {
        this->highlightedOption--;
      }
    } else if (IsKeyPressed(KEY_LEFT)) {
      this->highlightedOption--;
      if (this->highlightedOption < 0) {
        this->highlightedOption++;
      }
    }

    if (IsKeyPressed(KEY_ENTER)) {
      this->chooseSkillTree(this->highlightedOption);
    }

    return; // end no skill tree chosen
  }
}

void SkillTreeState::draw() {
  if (this->chosenSkillTree == nullptr) {
    // no tree chosen, draw choice of trees
    // TODO draw a title saying select a skill
    const int gap = 50;
    const int cardWidth = GetScreenWidth() / this->availableSkillTrees.size() -
                          (gap * (this->availableSkillTrees.size() + 1));
    const int cardHeight = 200;

    for (int i = 0; i < this->availableSkillTrees.size(); i++) {
      const int cardX = gap + (i * (cardWidth + gap));
      const int cardY = gap;

      this->drawTreePreview(cardX, cardY, cardWidth, cardHeight,
                            &this->availableSkillTrees[i],
                            i == this->highlightedOption);
    }

    return; // end no tree chosen
  }
}

SkillTreeState::~SkillTreeState() {
  // TODO
}
