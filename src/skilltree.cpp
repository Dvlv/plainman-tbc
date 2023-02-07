#include "headers/skilltree.h"
#include "raylib.h"
#include <string>
#include <vector>

SkillTree::SkillTree(std::string name, std::string description,
                     std::vector<SkillTreeNode> nodes) {
  this->className = name;
  this->description = description;
  this->nodes = nodes;
}

void SkillTree::draw() {
  // draw the skill tree
}

void SkillTree::update() {
  // update the skill tree
}

int SkillTree::getNumberOfLevels() const {
  int levels = 0;
  for (auto &node : nodes) {
    if (node.level > levels) {
      levels = node.level;
    }
  }

  return levels;
}

SkillTree::~SkillTree() { printf("SkillTree destructor called\n"); }
