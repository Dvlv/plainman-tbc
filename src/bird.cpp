#include "headers/bird.h"
#include "headers/attack.h"
#include "raylib.h"
#include <vector>

Bird::Bird(Rectangle pos)
    : Enemy(pos, "Bird", "A bird which can definitely fly.", 2, 1, 1,
            std::vector<Attack>{
                Attack("Peck", "A small peck", AttackType::KICK, 1, 0),
            }) {}
