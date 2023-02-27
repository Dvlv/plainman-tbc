#pragma once

#include "enums.h"

class Attack {
  public:
    // vars
    AttackElement element;
    int damage;
    int energyCost;

    // funcs
    Attack(AttackElement element, int damage, int energyCost);
};
