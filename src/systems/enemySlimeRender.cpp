#include "enemySlimeRender.hpp"

#include <SDL_render.h>

#include "components/enemy.hpp"
#include "components/texture.hpp"
#include "components/transform.hpp"
#include "entt/entt.hpp"
#include "util/camera.hpp"
#include "util/sdl_check.hpp"

void enemySlimeRender(entt::registry &reg, SDL_Renderer *renderer) {
  const auto view = reg.view<const Enemy, const Transform, Texture>();

  for (const auto e : view) {
    float fCameraPosX = Camera::Instance().getPosition().x;
    float fCameraPosY = Camera::Instance().getPosition().y;

    view.get<Texture>(e).dstRect.x = static_cast<int>(
        view.get<const Transform>(e).position2D.x - fCameraPosX);
    view.get<Texture>(e).dstRect.y = static_cast<int>(
        view.get<const Transform>(e).position2D.y - fCameraPosY);
    const auto &dstRect = view.get<Texture>(e).dstRect;

    auto currentFrame = static_cast<int>(((SDL_GetTicks() / 50) % 10));
    view.get<Texture>(e).srcRect.x = 44 * currentFrame;
    view.get<Texture>(e).srcRect.y = 30 * 0;

    const auto &srcRect = view.get<Texture>(e).srcRect;

    const auto texture = view.get<Texture>(e).texture;
    const auto angle = view.get<Texture>(e).angle;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_CHECK(SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle,
                               nullptr, flip));
  }
}
