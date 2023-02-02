#pragma once

#include "attack.h"
#include <memory>
#include <vector>

class SkillTreeNode {
public:
  SkillTreeNode(Attack *atk, int level, int skillPointCost);

  // vars
  Attack *atk;
  int level;
  int skillPointCost;

  // methods
  void draw();
  void update();

  ~SkillTreeNode() = default;
};
