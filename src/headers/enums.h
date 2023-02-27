#pragma once

enum class AttackElement {
    FIRE,
    AIR,
    EARTH,
    ICE,
    ELECTRIC,
    NONE,
};

enum class AttackType {
    MELEE,
    CAST,
};

enum class GameState {
    MENU,
    COMBAT,
    UPGRADE,
    SKILLTREE,
}
