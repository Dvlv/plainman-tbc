#include "headers/skilltree-state.h"
#include "headers/attack.h"
#include "headers/skilltree-node.h"
#include "headers/skilltree.h"
#include "raylib.h"
#include <vector>

SkillTreeState::SkillTreeState() {
  this->chosenSkillTree = nullptr;
  this->highlightedOption = 0;
  this->isFinished = false;

  this->availableSkillTrees = std::vector<SkillTree>{
      SkillTree(
          "Necromancer", "Summons Creatures to Attack",
          std::vector<SkillTreeNode>{
              SkillTreeNode(new Attack("Skeleton", "Summon a Skeleton",
                                       AttackType::SHOUT, 2, 2,
                                       AttackElement::FIRE),
                            1),
              SkillTreeNode(new Attack("Zombie", "Summon a Zombie",
                                       AttackType::SHOUT, 2, 2,
                                       AttackElement::ELECTRIC),
                            1),
              SkillTreeNode(new Attack("Dog", "Summon a Dog", AttackType::SHOUT,
                                       3, 2, AttackElement::ELECTRIC),
                            2),
          }),
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
      this->isFinished = true;
    }

    return; // end no skill tree chosen
  }
}

void SkillTreeState::draw() {
  const int gap = 50;

  if (this->chosenSkillTree == nullptr) {
    // no tree chosen, draw choice of trees
    // TODO draw a title saying select a skill
    const int cardWidth = ((GetScreenWidth() - (gap * 2)) -
                           (gap * (this->availableSkillTrees.size() - 1))) /
                          this->availableSkillTrees.size(); // 525
    const int cardHeight = 200;

    int titleLen = MeasureText("Choose a Speciality", 30);

    DrawText("Choose a Speciality", (GetScreenWidth() / 2) - (titleLen / 2),
             gap, 30, BLACK);

    for (int i = 0; i < this->availableSkillTrees.size(); i++) {
      const int cardX = gap + (i * (cardWidth + gap));
      const int cardY = gap * 2 + 30; // title font size

      this->drawTreePreview(cardX, cardY, cardWidth, cardHeight,
                            &this->availableSkillTrees[i],
                            i == this->highlightedOption);
    }

    return; // end no tree chosen
  }

  // otherwise, draw the chosen tree
  const int treeBgWidth = 500;
  const int treeBgX = GetScreenWidth() / 2 - treeBgWidth / 2;

  const int nodeWidth = 75;
  DrawRectangle(treeBgX, gap, treeBgWidth, GetScreenHeight() - gap * 2, BEIGE);

  DrawText(this->chosenSkillTree->className.c_str(),
           GetScreenWidth() / 2 -
               MeasureText(this->chosenSkillTree->className.c_str(), 30) / 2,
           gap * 2, 30, BLACK);

  // draw level one bg
  int currentLevel = 1;
  int levelBgY = gap * (3 * currentLevel);

  DrawRectangle(treeBgX + gap, levelBgY, treeBgWidth - gap * 2, 100, GRAY);

  // NOTE: this requires atks are added to a skilltree in order of level
  int idx = 1;
  for (auto &node : this->chosenSkillTree->nodes) {
    if (node.level > currentLevel) {
      currentLevel = node.level;
      idx = 1;
      levelBgY = gap * (3 * currentLevel);

      // draw next level bg
      DrawRectangle(treeBgX + gap, levelBgY, treeBgWidth - gap * 2, 100, GRAY);
    }

    // draw node
    DrawRectangle(treeBgX + gap + 10 + ((nodeWidth + 10) * (idx - 1)),
                  levelBgY + 10, nodeWidth, nodeWidth, PURPLE);
    idx++;
  }
}

SkillTreeState::~SkillTreeState() {
  // TODO
}
