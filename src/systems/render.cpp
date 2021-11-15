#include "render.hpp"

#include <SDL_render.h>

#include "components/direction.hpp"
#include "components/player.hpp"
#include "components/state.hpp"
#include "components/texture.hpp"
#include "components/transform.hpp"
#include "entt/entt.hpp"
#include "util/camera.hpp"
#include "util/sdl_check.hpp"

void playerRender(entt::registry &reg, SDL_Renderer *renderer) {
  const auto view = reg.view<const Player, const Transform, const Direction,
                             const State, Texture>();

  for (const auto e : view) {
    float fCameraPosX = Camera::Instance().getPosition().x;
    float fCameraPosY = Camera::Instance().getPosition().y;

    view.get<Texture>(e).dstRect.x = static_cast<int>(
        view.get<const Transform>(e).position2D.x - fCameraPosX);
    view.get<Texture>(e).dstRect.y = static_cast<int>(
        view.get<const Transform>(e).position2D.y - fCameraPosY);
    const auto &dstRect = view.get<Texture>(e).dstRect;

    // Player State Animation.
    if (view.get<const State>(e).state == plState::IDLE) {
      auto currentFrame = static_cast<int>(((SDL_GetTicks() / 50) % 11));
      view.get<Texture>(e).srcRect.x = 32 * currentFrame;
      view.get<Texture>(e).srcRect.y = 32 * 0;
    } else if (view.get<const State>(e).state == plState::RUN) {
      auto currentFrame = static_cast<int>(((SDL_GetTicks() / 50) % 12));
      view.get<Texture>(e).srcRect.x = 32 * currentFrame;
      view.get<Texture>(e).srcRect.y = 32 * 1;
    } else if (view.get<const State>(e).state == plState::JUMP) {
      view.get<Texture>(e).srcRect.x = 0;
      view.get<Texture>(e).srcRect.y = 32 * 2;
    } else if (view.get<const State>(e).state == plState::FALL) {
      view.get<Texture>(e).srcRect.x = 0;
      view.get<Texture>(e).srcRect.y = 32 * 3;
    }
    const auto &srcRect = view.get<Texture>(e).srcRect;

    const auto texture = view.get<Texture>(e).texture;
    const auto angle = view.get<Texture>(e).angle;

    // Player Direction.
    SDL_RendererFlip flip;
    if (view.get<const Direction>(e).dir == Dir::LEFT) {
      flip = SDL_FLIP_HORIZONTAL;
    } else {
      flip = SDL_FLIP_NONE;
    }

    SDL_CHECK(SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle,
                               nullptr, flip));
  }
}
