#pragma once

enum Animation {
  IDLE,
  ATTACK,
  MELEE_ATTACK,
  CAST_ATTACK,
  TAKE_DAMAGE,
};

enum MeleeAnimationState {
  FORWARD,
  ATTACKING,
  BACKWARD,
};
