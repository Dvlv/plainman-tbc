#pragma once

#include <string>

enum AttackType {
  PUNCH,
  KICK,
  SHOUT,
};

enum AttackElement {
  NONE,
  ELECTRIC,
  FIRE,
  ICE,
  EARTH,
  AIR,
};

class Attack {
public:
  AttackType atkType;
  std::string name;
  std::string description;
  int damage;
  int selfHeal;
  int energyCost;
  bool isAOE;
  AttackElement atkElement;

  // TODO energy cost
  Attack(std::string name, std::string description, AttackType atkType,
         int damage, int energyCost,
         AttackElement atkElement = AttackElement::NONE, bool isAOE = false,
         int selfHeal = 0);
};
