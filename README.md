# PlainMan - Endless Turn-Based Combat Game

## Building

```bash
mkdir build
./go.sh
```

## TODO
- [ ] Heal / Buff attacks
  - [x] Heal Atk
      - [x] Heal bubbles
  - [ ] Energy Atk
      - [ ] Energy bubbles
  - [ ] Charge atk
      - [ ] Charge bubble
- [ ] Make some kind of texture cache for cast effects so they arent racing
- [ ] Stat upgrade choice state
    - [ ] Swap isCombat flag for an enum
    - [ ] Transition anim between States, requires prevState in main
- [ ] More enemy classes
- [ ] Enemy immunities
- [ ] Proper lose condition
- [ ] Difficulty Tweaks

### Possible combat mechanics
- [ ] Status
    - [ ] Frozen / Para
    - [ ] Bleed / Fire
- [ ] Invincible Turn
- [ ] Heal Attacks
    - [ ] Life Steal
    - [ ] Heal bubble
- [ ] Charge

## Done

- [x] AoE Attacks
- [x] Left and Right work as expected in PlayerAtkMenu
- [x] Reset highlighted player attack to highest which you can afford if cant afford selected
- [x] Ability to read Combat rounds from a file, or randomly generate them?
- [x] Read Skill Trees from .h file
- [x] Menu disappear when attacking
- [x] Numbers in HP Bar
- [x] Show description of Attack in PlayerAttackMenu
- [x] Show description of enemy in PlayerAttackMenu
- [x] Attacks costing Energy
- [x] Display Energy on UI
- [x] Draw Player Animations
    - [x] Idle
    - [x] Attack / Walk?
    - [x] Cast
    - [x] Take Dmg
- [x] Player Animation logic
    - [x] Idle
    - [x] Attack / Walk?
    - [x] Cast
    - [x] Take Dmg
- [x] Outer GameState object which holds data about the player and whether it's map or combat
    - [x] Add stats to player
    - [x] Add skill points to player?
- [x] Skill Tree state
    - [x] Draw and select choice of skill tree
    - [x] Add new attacks to player
    - [x] Draw Skill Tree Attacks (just squares to start off with)
    - [x] Display name and desc of attack when hovering
    - [x] Skill points system
    - [x] Call chosen attack back to main.cpp state
- [x] Draw Enemy Animations
    - [x] Idle
    - [x] Attack / Walk?
    - [x] Cast
    - [x] Take Dmg
- [x] Enemy Animation Logic
    - [x] Idle
    - [x] Attack / Walk?
    - [x] Cast
    - [x] Take Dmg
- [x] Draw Sprites on attack
    - [x] Signal system so takeDamage is called after performing melee animation finishes and state goes to BACKWARDS
    - [x] Damage bubble class
    - [x] Damage bubble vector in CombatState which animates and marks self for deletion
    - [x] Draw elemental sprite over enemy on player using cast attack
- [x] Sprites for elemental types drawn
    - [x] Music (shout)
    - [x] Fire
    - [x] Electric
    - [x] Ice
    - [x] Earth
    - [x] Air



### QoL
- [ ] Easing animations
