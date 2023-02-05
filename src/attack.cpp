#include "headers/attack.h"

Attack::Attack(std::string name, std::string description, AttackType atkType,
               int damage, int energyCost, AttackElement atkElement, bool isAOE,
               int selfHeal) {
  this->name = name;
  this->atkType = atkType;
  this->damage = damage;
  this->atkElement = atkElement;
  this->description = description;
  this->energyCost = energyCost;
  this->isAOE = isAOE;
  this->selfHeal = selfHeal;
}
