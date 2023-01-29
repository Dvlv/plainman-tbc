# PlainMan - Endless Turn-Based Combat Game

## Building

```bash
mkdir build
cd build
./go.sh
```

## TODO
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

- [x] Draw Sprites on attack
    - [x] Signal system so takeDamage is called after performing melee animation finishes and state goes to BACKWARDS
    - [x] Damage bubble class
    - [x] Damage bubble vector in CombatState which animates and marks self for deletion
    - [ ] Sprites for elemental types drawn
        - [x] Music (shout)
        - [x] Fire
        - [x] Electric
        - [ ] Ice
        - [ ] Earth
        - [ ] Air
    - [x] Draw elemental sprite over enemy on player using cast attack
- [ ] Outer GameState object which holds data about the player and whether it's map or combat
    - [ ] Add stats to player
    - [ ] Add skill points to player?
    - [ ] Transition anim between combat and skilltree
- [ ] Skill Tree state
    - [x] Add new attacks to player
    - [ ] Draw Skill Tree (just squares to start off with)
    - [ ] Display name and desc of attack when hovering
    - [ ] Skill points system
    - [ ] Call chosen attack back to main.cpp state
- [x] Draw Enemy Animations
    - [x] Idle
    - [x] Attack / Walk?
    - [ ] Cast
    - [x] Take Dmg
- [x] Enemy Animation Logic
    - [x] Idle
    - [x] Attack / Walk?
    - [ ] Cast
    - [x] Take Dmg

- [ ] Ability to read Combat rounds from a file, or randomly generate them?
- [ ] More enemy classes
- [ ] Enemy immunities


### QoL
- [ ] Easing animations
