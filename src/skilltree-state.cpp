#include "headers/skilltree-state.h"
#include "headers/attack.h"
#include "headers/bard-skilltree.h"
#include "headers/brawler-skilltree.h"
#include "headers/mage-skilltree.h"
#include "headers/necromancer-skilltree.h"
#include "headers/skilltree-node.h"
#include "headers/skilltree.h"
#include "raylib.h"
#include <algorithm>
#include <vector>

#define STS_GAP 35

SkillTreeState::SkillTreeState() {
  this->chosenSkillTree = nullptr;
  this->highlightedOption = 0;
  this->isFinished = false;
  this->selectedAttack = nullptr;
  this->learnedAttacks = std::vector<int>();
  this->highestAttackLevel = 0;
  this->playerSkillPoints = 0;

  this->availableSkillTrees = std::vector<std::shared_ptr<SkillTree>>{
      std::make_shared<Necromancer>(),
      std::make_shared<Bard>(),
      std::make_shared<Mage>(),
      std::make_shared<Brawler>(),
  };
}

void SkillTreeState::chooseSkillTree(int skillTreeIndex) {
  this->chosenSkillTree = this->availableSkillTrees[skillTreeIndex];
  // empty this to free the memory of the 2 unused
  this->availableSkillTrees = std::vector<std::shared_ptr<SkillTree>>();
}

void SkillTreeState::drawTreePreview(int x, int y, int width, int height,
                                     std::shared_ptr<SkillTree> tree,
                                     bool isHighlighted) {
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

    bool isLearned =
        std::find(this->learnedAttacks.begin(), this->learnedAttacks.end(),
                  idx) != this->learnedAttacks.end();

    bool canLearn = node.level <= this->highestAttackLevel + 1 &&
                    node.skillPointCost <= this->playerSkillPoints;

    Color nodeColor = isLearned ? GREEN : canLearn ? PURPLE : RED;

    DrawRectangle(nodeX, nodeY, nodeWidth, nodeWidth, nodeColor);

    // draw cost
    DrawCircle(nodeX + nodeWidth - 10, nodeY + 10, 10, YELLOW);

    int numWidth = MeasureText(std::to_string(node.skillPointCost).c_str(), 20);

    DrawText(std::to_string(node.skillPointCost).c_str(),
             nodeX + nodeWidth - 10 - (numWidth / 2), nodeY + 1, 20, BLACK);

    posIdx++;
    idx++;
  }

  // total skill points
  std::string totalSkillPointsText =
      "Available Points: " + std::to_string(this->playerSkillPoints);

  DrawText(totalSkillPointsText.c_str(), treeBgX + STS_GAP, y + height - 50, 30,
           BLACK);
}

void SkillTreeState::drawAttackDescription(int x, int y, int width,
                                           int height) {
  const int padding = 25;
  DrawRectangle(x, y, width, height, BEIGE);

  if (this->chosenSkillTree != nullptr) {
    SkillTreeNode *node =
        &this->chosenSkillTree->nodes[this->highlightedOption];
    std::shared_ptr<Attack> atk = node->atk;

    DrawText(atk->name.c_str(), x + padding, y + padding, 30, BLACK);
    DrawText(atk->description.c_str(), x + padding, y + 30 + (padding * 2), 20,
             BLACK);

    int helpTextX = x + padding;
    int helpTextY = y + height - STS_GAP;

    if (node->skillPointCost > this->playerSkillPoints) {
      DrawText("Not enough skill points", helpTextX, helpTextY, 20, RED);

    } else if (node->level > this->highestAttackLevel + 1) {
      std::string helpText =
          "Requires attack from level " + std::to_string(node->level - 1);
      DrawText(helpText.c_str(), helpTextX, helpTextY, 20, RED);

    } else if (std::find(this->learnedAttacks.begin(),
                         this->learnedAttacks.end(), this->highlightedOption) !=
               this->learnedAttacks.end()) {

      DrawText("Learned", helpTextX, helpTextY, 20, RED);

    } else {
      DrawText("Learnable", helpTextX, helpTextY, 20, BLACK);
    }
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
  } else if (IsKeyPressed(KEY_DOWN)) {
    // select first atk on next level
    int atkLevel = this->chosenSkillTree->nodes[this->highlightedOption].level;
    for (int i = this->highlightedOption + 1;
         i < this->chosenSkillTree->nodes.size(); i++) {
      if (this->chosenSkillTree->nodes[i].level > atkLevel) {
        this->highlightedOption = i;
        break;
      }
    }
  } else if (IsKeyPressed(KEY_UP)) {
    // select last atk on previous level
    int atkLevel = this->chosenSkillTree->nodes[this->highlightedOption].level;
    for (int i = this->highlightedOption - 1; i >= 0; i--) {
      if (this->chosenSkillTree->nodes[i].level < atkLevel) {
        this->highlightedOption = i;
        break;
      }
    }
  }

  if (IsKeyPressed(KEY_ENTER)) {
    bool isLearned =
        std::find(this->learnedAttacks.begin(), this->learnedAttacks.end(),
                  this->highlightedOption) != this->learnedAttacks.end();

    bool canLearn =
        this->chosenSkillTree->nodes[this->highlightedOption].level <=
        this->highestAttackLevel + 1;

    if (!isLearned && canLearn) {
      this->selectedAttack =
          this->chosenSkillTree->nodes[this->highlightedOption].atk;

      this->selectedAttackSkillPointCost =
          this->chosenSkillTree->nodes[this->highlightedOption].skillPointCost;

      if (this->chosenSkillTree->nodes[this->highlightedOption].level >
          this->highestAttackLevel) {
        this->highestAttackLevel =
            this->chosenSkillTree->nodes[this->highlightedOption].level;
      }

      this->learnedAttacks.push_back(this->highlightedOption);
      this->highlightedOption = 0;
      this->isFinished = true;
    }
  } else if (IsKeyPressed(KEY_BACKSPACE)) {
    // cancel, TODO button
    this->selectedAttack = nullptr;
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
                            this->availableSkillTrees[i],
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
