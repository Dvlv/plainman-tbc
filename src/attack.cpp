#include "headers/attack.h"

Attack::Attack(std::string name, std::string description, AttackType atkType,
               int damage, int energyCost, AttackElement atkElement) {
  this->name = name;
  this->atkType = atkType;
  this->damage = damage;
  this->atkElement = atkElement;
  this->description = description;
  this->energyCost = energyCost;
}
