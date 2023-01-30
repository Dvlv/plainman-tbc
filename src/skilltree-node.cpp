#include "headers/skilltree-node.h"
#include "headers/attack.h"

SkillTreeNode::SkillTreeNode(Attack *atk, int level) {
  this->atk = atk;
  this->level = level;
}

void SkillTreeNode::update() {
  // update the skill tree node
}

void SkillTreeNode::draw() {
  // draw the skill tree node
}
