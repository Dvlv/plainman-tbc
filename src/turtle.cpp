#include "headers/turtle.h"
#include "headers/attack.h"
#include "raylib.h"
#include <vector>

Turtle::Turtle(Rectangle pos)
    : Enemy(pos, "Turtle", 3, 1, 1,
            std::vector<Attack>{
                Attack("Bite", AttackType::KICK, 2),
            }) {}
