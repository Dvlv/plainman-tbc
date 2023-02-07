#pragma once

#include "attack.h"
#include <memory>
#include <vector>

class SkillTreeNode {
public:
  SkillTreeNode(std::shared_ptr<Attack> atk, int level, int skillPointCost);

  // vars
  std::shared_ptr<Attack> atk;
  int level;
  int skillPointCost;

  // methods
  void draw();
  void update();

  ~SkillTreeNode() = default;
};
