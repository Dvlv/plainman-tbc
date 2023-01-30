#pragma once

#include "skilltree-node.h"
#include <string>
#include <vector>

class SkillTree {
public:
  SkillTree(std::string name, std::string description,
            std::vector<SkillTreeNode> nodes);

  // vars
  std::string className;
  std::string description;
  std::vector<SkillTreeNode> nodes;

  // methods
  void draw();
  void update();

  int getNumberOfLevels() const;

  ~SkillTree() = default;
};
