#ifndef NEWGAME_FACTORIES_HPP
#define NEWGAME_FACTORIES_HPP

#include <entt/entity/fwd.hpp>

entt::entity makePlayer(entt::registry &);

entt::entity makeEnemy(entt::registry &);

entt::entity makeBlobMenu(entt::registry &);

#endif  // NEWGAME_FACTORIES_HPP
