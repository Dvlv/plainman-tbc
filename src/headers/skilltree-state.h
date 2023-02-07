#pragma once

#include "attack.h"
#include "skilltree.h"
#include <memory>
#include <vector>

class SkillTreeState {
public:
  SkillTreeState();

  // vars
  std::shared_ptr<SkillTree> chosenSkillTree;
  std::vector<std::shared_ptr<SkillTree>> availableSkillTrees;
  int highlightedOption;
  std::vector<int> learnedAttacks;
  int highestAttackLevel;
  std::shared_ptr<Attack> selectedAttack;
  int selectedAttackSkillPointCost;
  int playerSkillPoints;
  bool isFinished;

  // funcs
  void chooseSkillTree(int skillTreeIndex);
  void drawTreePreview(int x, int y, int width, int height,
                       std::shared_ptr<SkillTree> tree, bool isHighlighted);
  void drawTree(int x, int y, int width, int height);
  void drawAttackDescription(int x, int y, int width, int height);
  void update();
  void draw();
  Attack getChosenAttack();

  ~SkillTreeState();
};
