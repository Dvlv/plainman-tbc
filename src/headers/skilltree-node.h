#pragma once

#include "attack.h"
#include <memory>
#include <vector>

class SkillTreeNode {
public:
  SkillTreeNode(Attack *atk, int level);

  // vars
  Attack *atk;
  int level;

  // methods
  void draw();
  void update();

  ~SkillTreeNode() = default;
};
