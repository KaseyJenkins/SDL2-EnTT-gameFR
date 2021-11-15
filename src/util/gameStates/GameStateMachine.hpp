#ifndef UTIL_GAMESTATEMACHINE_HPP_
#define UTIL_GAMESTATEMACHINE_HPP_

#include <entt/entity/fwd.hpp>
#include <vector>

namespace tinytmx {
class Map;
}

class GameStateMachine {
 public:
  GameStateMachine(class Game *gameP) : game(gameP) {}

  void logic();
  void render();

  void pushState(class GameState const *pState);
  void changeState(class GameState const *pState);
  void popState();

  std::vector<class GameState const *> const &getGameStates() const {
    return m_gameStates;
  }

 private:
  class Game *game;
  std::vector<class GameState const *> m_gameStates;
};

#endif  // UTIL_GAMESTATEMACHINE_HPP_