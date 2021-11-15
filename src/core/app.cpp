#include "app.hpp"

#include <SDL.h>

#include "core/constants.hpp"
#include "game.hpp"
#include "util/frame_cap.hpp"
#include "util/sdl_check.hpp"

Application::Application() { SDL_CHECK(SDL_Init(SDL_INIT_VIDEO)); }

Application::~Application() { SDL_Quit(); }

void Application::run() {
  Game::Instance().Init();

  while (Game::Instance().IsRunning()) {
    //        FrameCap sync{fps};

    Game::Instance().Input();

    Game::Instance().Logic();

    Game::Instance().Render();
  }

  Game::Instance().Clean();
}
