#include "factories.hpp"

#include <entt/entity/registry.hpp>

#include "components/blobMenu.hpp"
#include "components/direction.hpp"
#include "components/enemy.hpp"
#include "components/player.hpp"
#include "components/state.hpp"
#include "components/texture.hpp"
#include "components/transform.hpp"

entt::entity makePlayer(entt::registry &reg) {
  const entt::entity e = reg.create();
  reg.emplace<Player>(e);
  reg.emplace<Texture>(e);
  reg.emplace<Transform>(e);
  reg.emplace<Direction>(e, Dir::RIGHT);
  reg.emplace<State>(e, plState::IDLE);

  return e;
}

entt::entity makeEnemy(entt::registry &reg) {
  const entt::entity e = reg.create();
  reg.emplace<Enemy>(e);
  reg.emplace<Texture>(e);
  reg.emplace<Transform>(e);
  reg.emplace<Direction>(e, Dir::RIGHT);

  return e;
}

entt::entity makeBlobMenu(entt::registry &reg) {
  const entt::entity e = reg.create();
  reg.emplace<BlobMenu>(e);
  reg.emplace<Texture>(e);
  reg.emplace<Transform>(e);

  return e;
}
