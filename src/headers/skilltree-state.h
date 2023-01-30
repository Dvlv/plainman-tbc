#pragma once

#include "attack.h"
#include "skilltree.h"
#include <vector>

class SkillTreeState {
public:
  SkillTreeState();

  // vars
  SkillTree *chosenSkillTree;
  std::vector<SkillTree> availableSkillTrees;
  int highlightedOption;

  // funcs
  void chooseSkillTree(int skillTreeIndex);
  void drawTreePreview(int x, int y, int width, int height, SkillTree *tree,
                       bool isHighlighted);
  void update();
  void draw();
  Attack getChosenAttack();

  ~SkillTreeState();
};
