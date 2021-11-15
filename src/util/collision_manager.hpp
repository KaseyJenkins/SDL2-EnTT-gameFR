#ifndef NEWGAME_COLLISION_MANAGER_HPP
#define NEWGAME_COLLISION_MANAGER_HPP

#include <entt/entity/fwd.hpp>

namespace tinytmx {
class Map;
}

class CollisionManager {
 public:
  void checkPlayerTileCollision(tinytmx::Map *map, entt::registry &regV);
};

#endif  // NEWGAME_COLLISION_MANAGER_HPP
