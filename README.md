# PlainMan - Endless Turn-Based Combat Game

## Building

```bash
mkdir build
./go.sh
```

## TODO
- [ ] Outline enemies
- [ ] Ally Partners
- [x] Menu state
    - [ ] How2play
    - [ ] credits
- [ ] Continue message and Game Over Message in main.cpp
- [ ] Draw Backgrounds
    - [x] Combat
    - [ ] Upgrade
    - [ ] SkillTree
- [ ] More enemy classes
    - [x] Ghost
    - [ ] Skeleton
    - [ ] Frog
- [ ] Difficulty Tweaks
    - [ ] Make numbers bigger (hp, atk)
    - [ ] Add Randomness in damage calcs 
    - [ ] Randomness in enemy hp, dmg, energy

### Possible combat mechanics
- [ ] Status
    - [ ] Frozen / Para
    - [ ] Bleed / Fire
- [ ] Invincible Turn
- [ ] Charge

## Done
- [x] Proper lose condition
- [x] 1 Continue
- [x] Enemy immunities
- [x] Cast effect on melee if atkelement
- [x] Allow AoE PUNCH attacks
- [x] Transition anim between States, requires prevState in main
- [x] Global texture handler with array of textures and returns an ID, then all unloaded on destroy
- [x] Dont show enemy select or play damage anim on a pure-heal atk
- [x] Heal / Buff attacks
  - [x] Heal Atk
      - [x] Heal bubbles
  - [x] Energy Atk
      - [x] Energy bubbles
- [x] Replace all raw pointers with smarts
- [x] Stat upgrade choice state
    - [x] Swap isCombat flag for an enum
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
