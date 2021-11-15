#include "blobMenuRender.hpp"

#include <SDL_render.h>

#include "components/blobMenu.hpp"
#include "components/texture.hpp"
#include "components/transform.hpp"
#include "entt/entt.hpp"
#include "util/camera.hpp"
#include "util/sdl_check.hpp"

void blobMenuRender(entt::registry &reg, class SDL_Renderer *renderer) {
  const auto view = reg.view<const BlobMenu, const Transform, Texture>();

  for (const auto e : view) {
    view.get<Texture>(e).dstRect.x =
        static_cast<int>(view.get<const Transform>(e).position2D.x);
    view.get<Texture>(e).dstRect.y =
        static_cast<int>(view.get<const Transform>(e).position2D.y);
    const auto &dstRect = view.get<Texture>(e).dstRect;

    const auto &srcRect = view.get<Texture>(e).srcRect;

    const auto texture = view.get<Texture>(e).texture;
    const auto angle = view.get<Texture>(e).angle;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_CHECK(SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle,
                               nullptr, flip));
  }
}
