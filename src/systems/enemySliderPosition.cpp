#include "enemySliderPosition.hpp"

#include <entt/entity/registry.hpp>

#include "components/direction.hpp"
#include "components/enemy.hpp"
#include "components/texture.hpp"
#include "components/transform.hpp"

void enemySliderMovement(entt::registry &reg, float dt) {
  const auto view = reg.view<const Enemy, Transform, Texture, Direction>();

  for (const auto e : view) {
    auto &pos = view.get<Transform>(e).position2D;
    auto &dir = view.get<Direction>(e).dir;
  }
}
