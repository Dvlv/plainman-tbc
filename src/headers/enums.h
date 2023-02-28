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
    CAST_AOE,
    HEAL_TARGET,
    HEAL_SELF,
    HEAL_AOE,
};

enum class GameState {
    MENU,
    COMBAT,
    UPGRADE,
    SKILLTREE,
};

enum class CombatStateTurn {
    Ally,
    Enemy,
};
