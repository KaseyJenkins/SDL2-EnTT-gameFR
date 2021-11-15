#include "MainMenuState.hpp"

#include <SDL_render.h>

#include <iostream>

#include "components/blobMenu.hpp"
#include "components/texture.hpp"
#include "components/transform.hpp"
#include "core/factories.hpp"
#include "core/game.hpp"
#include "systems/blobMenuPosition.hpp"
#include "systems/blobMenuRender.hpp"
#include "systems/enemySlimeRender.hpp"
#include "systems/tileRender.hpp"
#include "util/font/font.hpp"
#include "util/sdl_check.hpp"
#include "util/texture_manager.hpp"

std::string const MainMenuState::s_menuID = "MAIN_MENU";

void MainMenuState::logic(Game *game) const {
  auto &reg = game->getReg();
  auto *m_pGameStateMachine = game->getGameStateMachine();

  blobMenumovement(reg, m_pGameStateMachine);
}

void MainMenuState::render(Game *game) const {
  auto *m_pRenderer = game->getSDL_Renderer();
  // Set the window to the color we want.
  SDL_CHECK(SDL_SetRenderDrawColor(m_pRenderer, 33, 33, 33, 255));
  // Clear the last frame
  SDL_CHECK(SDL_RenderClear(m_pRenderer));

  // 'start' Main Menu text.
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = 78;
  srcRect.h = destRect.h = 36;
  destRect.x = 200;
  destRect.y = 250;

  SDL_Texture *texture =
      TextureManager::Instance().getTextureMap().at("idStartText");
  SDL_CHECK(SDL_RenderCopyEx(m_pRenderer, texture, &srcRect, &destRect, 0,
                             nullptr, SDL_FLIP_NONE));

  // 'quit' Main Menu text.
  srcRect.w = destRect.w = 56;
  srcRect.h = destRect.h = 36;
  destRect.y = 290;

  texture = TextureManager::Instance().getTextureMap().at("idQuitText");
  SDL_CHECK(SDL_RenderCopyEx(m_pRenderer, texture, &srcRect, &destRect, 0,
                             nullptr, SDL_FLIP_NONE));

  auto &reg = game->getReg();
  blobMenuRender(reg, m_pRenderer);
}

bool MainMenuState::onEnter(Game *game) const {
  auto *m_pRenderer = game->getSDL_Renderer();
  // Load 'start' text textures.
  TextureManager::Instance().LoadText("assets/font/pricedownbl.ttf", "start",
                                      "idStartText", m_pRenderer);
  TextureManager::Instance().LoadText("assets/font/pricedownbl.ttf", "quit",
                                      "idQuitText", m_pRenderer);

  // Create a menu 'blob'.
  auto &reg = game->getReg();
  const entt::entity blobMenu = makeBlobMenu(reg);
  reg.get<Texture>(blobMenu).texture = TextureManager::Instance().Load(
      "assets/blobMenu.png", "idBlobMenu", m_pRenderer);
  reg.get<Texture>(blobMenu).srcRect = {0, 0, 32, 32};
  reg.get<Texture>(blobMenu).dstRect = {0, 0, 32, 32};
  reg.get<Transform>(blobMenu).position2D.x = 160;
  reg.get<Transform>(blobMenu).position2D.y = 250;

  return true;
}

bool MainMenuState::onExit(Game *game) const {
  // Destroys all the entities in a range.
  auto &reg = game->getReg();
  auto view = reg.view<BlobMenu, Texture, Transform>();
  reg.destroy(view.begin(), view.end());

  // Destroys the textures.
  auto &textureMap = TextureManager::Instance().getTextureMapDelete();
  SDL_DestroyTexture(textureMap["idBlobMenu"]);
  SDL_DestroyTexture(textureMap["idQuitText"]);
  SDL_DestroyTexture(textureMap["idStartText"]);
  // TextureManager::Instance().clearFromTextureMap("idBlobMenu");
  // TextureManager::Instance().clearFromTextureMap("idQuitText");
  // TextureManager::Instance().clearFromTextureMap("idStartText");

  return true;
}
