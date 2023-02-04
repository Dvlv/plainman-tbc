#pragma once

#include "attack.h"
#include "skilltree-node.h"
#include "skilltree.h"
#include <vector>

class Necromancer : public SkillTree {
public:
  Necromancer()
      : SkillTree(
            "Necromancer", "Summons Allies and Saps\n Enemy HP",
            std::vector<SkillTreeNode>{
                SkillTreeNode(new Attack("Zombie", "Summon a Zombie.\n1 Energy",
                                         AttackType::SHOUT, 1, 1,
                                         AttackElement::FIRE),
                              1, 1),
                SkillTreeNode(new Attack("Skeleton",
                                         "Summon a Skeleton.\n1 Energy",
                                         AttackType::SHOUT, 1, 1,
                                         AttackElement::ELECTRIC),
                              1, 1),
                SkillTreeNode(
                    new Attack("Vampire", "Summon a Vampire.\n2 Energy",
                               AttackType::SHOUT, 2, 2, AttackElement::ICE),
                    2, 1),
                SkillTreeNode(
                    new Attack("Twin-Headed Zombie",
                               "Summon a Two-Headed Zombie.\n3 Energy",
                               AttackType::SHOUT, 3, 3, AttackElement::EARTH),
                    2, 2),
                SkillTreeNode(
                    new Attack("Abomination", "Summon...Something.\n4 Energy",
                               AttackType::SHOUT, 4, 4, AttackElement::AIR),
                    3, 3),
                SkillTreeNode(new Attack("Life Leech",
                                         "Throws Leech onto Enemy to Steal "
                                         "HP.\n5 Damage\n5 Energy",
                                         AttackType::SHOUT, 5, 5,
                                         AttackElement::FIRE),
                              3, 4),

                SkillTreeNode(
                    new Attack("Summon Snack",
                               "Resurrect a Tasty Snack.\n+3 HP\n1 Energy",
                               AttackType::SHOUT, 0, 1,
                               AttackElement::ELECTRIC),
                    3, 5),
                SkillTreeNode(
                    new Attack("Summon Armour",
                               "Summon a Suit of Armor.\n+2 HP\n3 Energy",
                               AttackType::SHOUT, 0, 3, AttackElement::ICE),
                    4, 6),

                SkillTreeNode(new Attack("Twin Skeletons",
                                         "Summon Two Skeletons.\n8 Energy",
                                         AttackType::SHOUT, 0, 8,
                                         AttackElement::NONE),
                              4, 5),
            }) {}
};
