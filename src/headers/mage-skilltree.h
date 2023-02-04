#pragma once

#include "attack.h"
#include "skilltree-node.h"
#include "skilltree.h"
#include <vector>

class Mage : public SkillTree {
public:
  Mage()
      : SkillTree(
            "Mage", "Uses Elemental Casts",
            std::vector<SkillTreeNode>{
                SkillTreeNode(new Attack("Fireball",
                                         "Cast a Fireball.\n1 Damage\n1 Energy",
                                         AttackType::SHOUT, 1, 1,
                                         AttackElement::FIRE),
                              1, 1),
                SkillTreeNode(
                    new Attack(
                        "Thunderzap", "Zap with Thunder.\n1 Damage\n1 Energy",
                        AttackType::SHOUT, 1, 1, AttackElement::ELECTRIC),
                    1, 1),
                SkillTreeNode(new Attack("Ice Blast",
                                         "Blast with Ice. \n2 Damage\n2 Energy",
                                         AttackType::SHOUT, 2, 2,
                                         AttackElement::ICE),
                              2, 1),
                SkillTreeNode(
                    new Attack("Mud Ball",
                               "Throw a Mud Ball.\n3 Damage\n3 Energy",
                               AttackType::SHOUT, 3, 3, AttackElement::EARTH),
                    2, 2),
                SkillTreeNode(new Attack("Air Blast",
                                         "Blast with Air.\n4 Damage\n4 Energy",
                                         AttackType::SHOUT, 4, 4,
                                         AttackElement::AIR),
                              3, 3),
                SkillTreeNode(
                    new Attack("Fire Spout", "Spout Fire.\n5 Damage\n5 Energy",
                               AttackType::SHOUT, 5, 5, AttackElement::FIRE),
                    3, 4),

                SkillTreeNode(
                    new Attack("Electric Storm",
                               "Cause an Electric Storm.\n6 Damage\n5 Energy",
                               AttackType::SHOUT, 6, 5,
                               AttackElement::ELECTRIC),
                    3, 5),
                SkillTreeNode(
                    new Attack("Blizzard",
                               "Summon a Blizzard.\n7 Damage\n6 Energy",
                               AttackType::SHOUT, 7, 6, AttackElement::ICE),
                    4, 6),

                SkillTreeNode(
                    new Attack("Eardrum Assault",
                               "Cause a Loud Noise.\n8 Damage\n8 Energy",
                               AttackType::SHOUT, 8, 8, AttackElement::NONE),
                    4, 5),
            }) {}
};
