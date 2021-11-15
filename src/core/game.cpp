#include "game.hpp"

#include <SDL.h>
#include <SDL_ttf.h>

#include "constants.hpp"
#include "tinytmx/tinytmx.hpp"
#include "util/dt.hpp"
#include "util/gameStates/GameStateMachine.hpp"
#include "util/gameStates/MainMenuState.hpp"
#include "util/sdl_check.hpp"
#include "util/texture_manager.hpp"

int getScaleFactor() {
  // Make the largest window possible with an integer scale factor
  SDL_Rect bounds;
#if SDL_VERSION_ATLEAST(2, 0, 5)
  SDL_CHECK(SDL_GetDisplayUsableBounds(0, &bounds));
#else
#warning SDL 2.0.5 or later is recommended
  SDL_CHECK(SDL_GetDisplayBounds(0, &bounds));
#endif
  const int scaleX = bounds.w / tilesPx.x;
  const int scaleY = bounds.h / tilesPx.y;
  return std::max(1, std::min(scaleX, scaleY));
}

Game::Game()
    : m_pWindow(nullptr),
      m_pRenderer(nullptr),
      tmxMap(nullptr),
      m_pGameStateMachine(nullptr),
      dt(0) {}

void Game::Init() {
  int const scaleFactor = getScaleFactor();

  m_pWindow = {SDL_CHECK(SDL_CreateWindow(
      "GameTrial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      tilesPx.x * scaleFactor, tilesPx.y * scaleFactor, SDL_WINDOW_SHOWN))};

  m_pRenderer = {SDL_CHECK(SDL_CreateRenderer(
      m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))};
  SDL_CHECK(SDL_RenderSetLogicalSize(m_pRenderer, tilesPx.x, tilesPx.y));

  // Initialize SDL TTF
  TTF_Init();

  // Initialize Game State.
  m_pGameStateMachine = new GameStateMachine(this);
  m_pGameStateMachine->changeState(new MainMenuState());
}

void Game::Logic() {
  dt = deltaTimeTicks();
  m_pGameStateMachine->logic();
}

void Game::Render() {
  // Set the window to the color we want.
  SDL_CHECK(SDL_SetRenderDrawColor(m_pRenderer, 56, 172, 236, 255));
  // Clear the last frame.
  SDL_CHECK(SDL_RenderClear(m_pRenderer));

  m_pGameStateMachine->render();

  // Update screen
  SDL_RenderPresent(m_pRenderer);
}

void Game::LoadAllTilesets() {
  for (int i = 0; i < tmxMap->GetNumTilesets(); ++i) {
    std::string fileName =
        tmxMap->GetFilepath() + tmxMap->GetTileset(i)->GetImage()->GetSource();
    TextureManager::Instance().Load(fileName, tmxMap->GetTileset(i)->GetName(),
                                    m_pRenderer);
  }
}

void Game::Clean() {
  SDL_DestroyRenderer(m_pRenderer);
  SDL_DestroyWindow(m_pWindow);
  TTF_Quit();
}
