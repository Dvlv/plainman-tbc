#pragma once

#include "attack.h"
#include <vector>

class NecromancerSkilltree {
public:
  NecromancerSkilltree();
  std::vector<Attack> level1Attacks;
  std::vector<Attack> level2Attacks;
};
