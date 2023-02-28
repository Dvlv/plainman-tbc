#include "combat-entity.h"
#include "player.h"
#include "raylib.h"
#include <memory>
#include <vector>

using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;

// type defs
using CombatEntities = std::vector<shared_ptr<CombatEntity>>;

class CombatState {
  public:
    CombatState();

    void update();
    void draw();

  private:
    unique_ptr<Player> player = make_unique<Player>();
    CombatEntities enemies{};
    CombatEntities allies{};
};
