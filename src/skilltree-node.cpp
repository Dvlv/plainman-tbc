#include "headers/skilltree-node.h"
#include "headers/attack.h"

SkillTreeNode::SkillTreeNode(std::shared_ptr<Attack> atk, int level,
                             int skillPointCost) {
  this->atk = atk;
  this->level = level;
  this->skillPointCost = skillPointCost;
}

void SkillTreeNode::update() {
  // update the skill tree node
}

void SkillTreeNode::draw() {
  // draw the skill tree node
}
