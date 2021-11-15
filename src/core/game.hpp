#ifndef NEWGAME_GAME_HPP
#define NEWGAME_GAME_HPP

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_scancode.h>

#include <entt/entity/registry.hpp>

#include "util/input_handler.hpp"

namespace tinytmx {
class Map;
}

class Game {
 public:
  // Singleton.
  static Game &Instance() {
    static Game s_pInstance;
    return s_pInstance;
  }
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;

  void Init();

  void LoadAllTilesets();  // done

  void Input() { InputHandler::Instance().update(m_pGameStateMachine); }

  void Logic();

  void Render();

  void Clean();

  bool IsRunning() const { return m_bRunning; }

  void quit() { m_bRunning = false; }

  bool onTheGround = false;

  float getDT() { return dt; }

  SDL_Renderer *getSDL_Renderer() const { return m_pRenderer; }
  class GameStateMachine *getGameStateMachine() const {
    return m_pGameStateMachine;
  }
  tinytmx::Map *getMap() const { return tmxMap; }
  entt::registry &getReg() { return reg; }

  tinytmx::Map **getMapPtr() { return &tmxMap; }

 private:
  Game();

  bool m_bRunning = true;

  float dt;

  entt::registry reg;

  SDL_Window *m_pWindow;
  SDL_Renderer *m_pRenderer;

  tinytmx::Map *tmxMap;

  class GameStateMachine *m_pGameStateMachine;
};

#endif  // NEWGAME_GAME_HPP
