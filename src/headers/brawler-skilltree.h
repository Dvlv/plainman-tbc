#pragma once

#include "attack.h"
#include "skilltree-node.h"
#include "skilltree.h"
#include <memory>
#include <vector>

class Brawler : public SkillTree {
public:
  Brawler()
      : SkillTree(
            "Brawler", "Fight with your fists",
            std::vector<SkillTreeNode>{
                SkillTreeNode(
                    std::make_shared<Attack>(
                        "ThunderPunch",
                        "A punch that shocks the enemy\n1 Damage\n1 Energy",
                        AttackType::PUNCH, 1, 1, AttackElement::ELECTRIC),
                    1, 1),
                SkillTreeNode(
                    std::make_shared<Attack>(
                        "FirePunch",
                        "A punch that burns the enemy\n1 Damage\n1 Energy",
                        AttackType::PUNCH, 1, 1, AttackElement::FIRE),
                    1, 1),
                SkillTreeNode(
                    std::make_shared<Attack>(
                        "Ice Punch",
                        "A punch that freezes the enemy\n1 Damage\n1 Energy",
                        AttackType::PUNCH, 1, 1, AttackElement::ICE, false, 1),
                    1, 1),
                SkillTreeNode(
                    std::make_shared<Attack>(
                        "Earth Punch",
                        "Punch the ground by the enemy\n1 Damage\n1 Energy",
                        AttackType::PUNCH, 1, 1, AttackElement::EARTH, false,
                        1),
                    1, 1),
                SkillTreeNode(std::make_shared<Attack>(
                                  "Chest Punch",
                                  "Shout to pump yourself up\n+1 HP, +2 Energy",
                                  AttackType::SHOUT, 0, 0, AttackElement::NONE,
                                  false, 1, 2),
                              2, 1),
                SkillTreeNode(std::make_shared<Attack>(
                                  "Thief Punch",
                                  "Steal HP from an enemy\n2 Damage\n2 Energy",
                                  AttackType::PUNCH, 2, 2, AttackElement::NONE,
                                  true, 2),
                              2, 2),
                SkillTreeNode(std::make_shared<Attack>(
                                  "Jumping Punch",
                                  "Jump into the air with an uppercut\n3 "
                                  "Damage\n3 Energy",
                                  AttackType::PUNCH, 3, 3, AttackElement::AIR),
                              2, 2),
                SkillTreeNode(std::make_shared<Attack>(
                                  "Double-Fire Punch",
                                  "Punch with fire...twice\n4 Damage\n3 Energy",
                                  AttackType::PUNCH, 4, 3, AttackElement::AIR),
                              3, 3),
                SkillTreeNode(
                    std::make_shared<Attack>("Super Punch",
                                             "Very strong punch"
                                             "HP.\n8 Damage\n6 Energy",
                                             AttackType::PUNCH, 8, 6,
                                             AttackElement::NONE, false),
                    3, 4),

                SkillTreeNode(
                    std::make_shared<Attack>("Punch-All",
                                             "Punch all enemies in one"
                                             "HP.\n4 Damage\n6 Energy",
                                             AttackType::PUNCH, 4, 6,
                                             AttackElement::NONE, true),
                    3, 4),

                SkillTreeNode(std::make_shared<Attack>(
                                  "Eat Energy Bar", "Restore 5 HP and 5 Energy",
                                  AttackType::SHOUT, 0, 0,
                                  AttackElement::ELECTRIC, false, 5, 5),
                              3, 5),
                SkillTreeNode(std::make_shared<Attack>(
                                  "Summon Armour",
                                  "Summon a Suit of Armor.\n+2 HP\n3 Energy",
                                  AttackType::SHOUT, 0, 3, AttackElement::ICE),
                              4, 6),

                SkillTreeNode(std::make_shared<Attack>(
                                  "Twin Skeletons",
                                  "Summon Two Skeletons.\n8 Energy",
                                  AttackType::SHOUT, 0, 8, AttackElement::NONE),
                              4, 5),
            }) {}
};
