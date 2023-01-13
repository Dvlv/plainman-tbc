#pragma once

#include <string>

enum AttackType {
  PUNCH,
  KICK,
  SHOUT,
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
  int damage;
  int animationFrames; // TODO better type

  Attack(std::string name, AttackType atkType, int damage);
};
