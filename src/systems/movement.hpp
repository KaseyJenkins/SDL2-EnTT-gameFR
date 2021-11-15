#ifndef NEWGAME_MOVEMENT_HPP
#define NEWGAME_MOVEMENT_HPP

#include <entt/entity/fwd.hpp>

namespace tinytmx {
class Map;
}

// This moves the player.
void movement(entt::registry &, tinytmx::Map *, class GameStateMachine *,
              float);

#endif  // NEWGAME_MOVEMENT_HPP
