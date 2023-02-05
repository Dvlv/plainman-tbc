#pragma once

#include "attack.h"
#include "skilltree-node.h"
#include "skilltree.h"
#include <vector>

class Bard : public SkillTree {
public:
  Bard()
      : SkillTree(
            "Bard", "Plays Music for Buffs",
            std::vector<SkillTreeNode>{
                SkillTreeNode(
                    new Attack("Loud Song",
                               "A Loud Song heard by all.\n2 Damage\n1 Energy",
                               AttackType::SHOUT, 1, 1, AttackElement::NONE,
                               true),
                    1, 1),
                SkillTreeNode(new Attack("Healing Song",
                                         "A soothing melody.\n+2 HP\n1 Energy",
                                         AttackType::SHOUT, 0, 1,
                                         AttackElement::NONE, false, 2),
                              1, 1),
                SkillTreeNode(new Attack("Cool Song",
                                         "A Cool Melody. \n2 Damage\n1 Energy",
                                         AttackType::SHOUT, 2, 1,
                                         AttackElement::ICE),
                              2, 1),
                SkillTreeNode(
                    new Attack("Heavy Metal Song",
                               "Blast Some Noise.\n3 Damage\n3 Energy",
                               AttackType::SHOUT, 3, 3,
                               AttackElement::ELECTRIC),
                    2, 2),
                SkillTreeNode(
                    new Attack("Dance Track", "Get Pumped.\n+2HP\n2 Energy",
                               AttackType::SHOUT, 0, 2, AttackElement::AIR),
                    3, 3),
                SkillTreeNode(
                    new Attack("Calm Song", "A Calm Melody.\n+3 Energy",
                               AttackType::SHOUT, 0, 0, AttackElement::NONE),
                    3, 4),

                SkillTreeNode(
                    new Attack(
                        "Punk Rock", "Blasts all Enemies.\n2 Damage\n6 Energy",
                        AttackType::SHOUT, 2, 6, AttackElement::ELECTRIC),
                    3, 5),
                SkillTreeNode(
                    new Attack("Jazz",
                               "Cools All Allies.\n+2 HP +2 Energy\nAll Allies",
                               AttackType::SHOUT, 0, 6, AttackElement::NONE),
                    4, 6),

                SkillTreeNode(
                    new Attack("Shred",
                               "Shreds the Guitar.\n8 Damage\n8 Energy",
                               AttackType::SHOUT, 8, 8, AttackElement::FIRE),
                    4, 5),
            }) {}
};
