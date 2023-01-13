#include "headers/attack.h"

Attack::Attack(std::string name, AttackType atkType, int damage) {
  this->name = name;
  this->atkType = atkType;
  this->damage = damage;
}
