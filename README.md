# PlainMan - Endless Turn-Based Combat Game

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
        - [ ] Fire
        - [ ] Electric
        - [ ] Ice
        - [ ] Earth
        - [ ] Air
    - [x] Draw elemental sprite over enemy on player using cast attack
- [ ] Outer GameState object which holds data about the player and whether it's map or combat
    - [x] Add new attacks to player
    - [ ] Add stats to player
    - [ ] Map state
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
