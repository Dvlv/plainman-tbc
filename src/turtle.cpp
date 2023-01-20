#include "headers/turtle.h"
#include "headers/attack.h"
#include "raylib.h"
#include <vector>

Turtle::Turtle(Rectangle pos)
    : Enemy(pos, "Turtle", "A small turtle. Kind of cute.", 3, 1, 1,
            std::vector<Attack>{
                Attack("Bite", "A small bite", AttackType::KICK, 2),
            }) {}
