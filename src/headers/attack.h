#pragma once

#include "enums.h"

class Attack {
  public:
    // vars
    AttackElement element;
    AttackType type;
    int power;
    int cost;

    // funcs
    Attack(AttackType type, int damage, int energyCost, AttackElement element);
};
