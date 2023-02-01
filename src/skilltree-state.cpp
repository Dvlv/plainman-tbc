#include "headers/skilltree-state.h"
#include "headers/attack.h"
#include "headers/skilltree-node.h"
#include "headers/skilltree.h"
#include "raylib.h"
#include <vector>

#define STS_GAP 40

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

void SkillTreeState::drawTree(int treeBgX, int y, int treeBgWidth, int height) {
  const int nodeWidth = 75;

  DrawRectangle(treeBgX, y, treeBgWidth, height, BEIGE);

  DrawText(this->chosenSkillTree->className.c_str(),
           (treeBgX + treeBgWidth) / 2, y + STS_GAP, 30, BLACK);

  // draw level one bg
  int currentLevel = 1;
  int levelBgY = y + STS_GAP * (3 * currentLevel);

  DrawRectangle(treeBgX + STS_GAP, levelBgY, treeBgWidth - STS_GAP * 2, 100,
                GRAY);

  // NOTE: this requires atks are added to a skilltree in order of level
  int idx = 0;
  int posIdx = 1;
  for (auto &node : this->chosenSkillTree->nodes) {
    if (node.level > currentLevel) {
      currentLevel = node.level;
      posIdx = 1;
      levelBgY = y + STS_GAP * (3 * currentLevel);

      // draw next level bg
      DrawRectangle(treeBgX + STS_GAP, levelBgY, treeBgWidth - STS_GAP * 2, 100,
                    GRAY);
    }

    // draw node
    int nodeX = treeBgX + STS_GAP + 10 + ((nodeWidth + 10) * (posIdx - 1));
    int nodeY = levelBgY + 10;

    if (idx == this->highlightedOption) {
      DrawRectangle(nodeX - 5, nodeY - 5, nodeWidth + 10, nodeWidth + 10,
                    SKYBLUE);
    }

    DrawRectangle(nodeX, nodeY, nodeWidth, nodeWidth, PURPLE);
    posIdx++;
    idx++;
  }
}

void SkillTreeState::drawAttackDescription(int x, int y, int width,
                                           int height) {
  const int padding = 25;
  DrawRectangle(x, y, width, height, BEIGE);

  if (this->chosenSkillTree != nullptr) {
    Attack *atk = this->chosenSkillTree->nodes[this->highlightedOption].atk;

    DrawText(atk->name.c_str(), x + padding, y + padding, 30, BLACK);
    DrawText(atk->description.c_str(), x + padding, y + 30 + (padding * 2), 20,
             BLACK);
  }
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
      this->highlightedOption = 0;
      this->isFinished = true;
    }

    return; // end no skill tree chosen
  }

  // skill tree chosen, listen for keyboard event to change selected attack to
  // learn
  //
  if (IsKeyPressed(KEY_RIGHT)) {
    this->highlightedOption++;
    if (this->highlightedOption >= this->chosenSkillTree->nodes.size()) {
      this->highlightedOption--;
    }
  } else if (IsKeyPressed(KEY_LEFT)) {
    this->highlightedOption--;
    if (this->highlightedOption < 0) {
      this->highlightedOption++;
    }
  }

  if (IsKeyPressed(KEY_ENTER)) {
    // TODO call attack back to main state
    this->highlightedOption = 0;
    this->isFinished = true;
  }
}

void SkillTreeState::draw() {
  if (this->chosenSkillTree == nullptr) {
    // no tree chosen, draw choice of trees
    // TODO draw a title saying select a skill
    const int cardWidth = ((GetScreenWidth() - (STS_GAP * 2)) -
                           (STS_GAP * (this->availableSkillTrees.size() - 1))) /
                          this->availableSkillTrees.size(); // 525
    const int cardHeight = 200;

    int titleLen = MeasureText("Choose a Speciality", 30);

    DrawText("Choose a Speciality", (GetScreenWidth() / 2) - (titleLen / 2),
             STS_GAP, 30, BLACK);

    for (int i = 0; i < this->availableSkillTrees.size(); i++) {
      const int cardX = STS_GAP + (i * (cardWidth + STS_GAP));
      const int cardY = STS_GAP * 2 + 30; // title font size

      this->drawTreePreview(cardX, cardY, cardWidth, cardHeight,
                            &this->availableSkillTrees[i],
                            i == this->highlightedOption);
    }

    return; // end no tree chosen
  }

  // otherwise, draw the chosen tree
  const int treeBgWidth = 500;
  const int descriptionBgWidth = 350;
  const int treeBgX =
      GetScreenWidth() / 2 - treeBgWidth / 2 - (descriptionBgWidth / 2);
  const int descriptionBgX = GetScreenWidth() - descriptionBgWidth - STS_GAP;

  int titleWidth = MeasureText("Choose an Attack to Learn", 30);
  DrawText("Choose an Attack to Learn",
           (GetScreenWidth() / 2) - (titleWidth / 2), STS_GAP, 30, BLACK);

  this->drawTree(treeBgX, (STS_GAP * 2) + 30, treeBgWidth,
                 GetScreenHeight() - STS_GAP * 4);

  this->drawAttackDescription(descriptionBgX, (STS_GAP * 2) + 30,
                              descriptionBgWidth, (GetScreenHeight() / 2));
}

SkillTreeState::~SkillTreeState() {
  // TODO
}
