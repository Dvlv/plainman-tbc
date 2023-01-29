#include "headers/necromancer-skilltree.h"

NecromancerSkilltree::NecromancerSkilltree() {
  // TODO loadLevelXAttacks method if this uses too much RAMS
  this->level1Attacks = std::vector<Attack>{
      Attack("Skeleton", "Summon a Skeleton", AttackType::SHOUT, 2, 2,
             AttackElement::FIRE),
      Attack("Zombie", "Summon a Zombie", AttackType::SHOUT, 3, 3,
             AttackElement::ELECTRIC),
  };
  this->level2Attacks = std::vector<Attack>{
      Attack("Dog", "Resurrect a Dog", AttackType::SHOUT, 4, 4,
             AttackElement::NONE),
      Attack("Cat", "Resurrect a Cat", AttackType::SHOUT, 3, 3,
             AttackElement::NONE),
  };
}
