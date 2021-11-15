#ifndef UTIL_MAINMENUSTATE_HPP_
#define UTIL_MAINMENUSTATE_HPP_

#include <entt/entity/fwd.hpp>

#include "GameState.hpp"

namespace tinytmx {
class Map;
}

class MainMenuState : public GameState {
 public:
  void logic(class Game *) const override;
  void render(class Game *) const override;

  bool onEnter(class Game *) const override;
  bool onExit(class Game *) const override;

  std::string const &getStateID() const override { return s_menuID; }

 private:
  static const std::string s_menuID;
};

#endif  // UTIL_MAINMENUSTATE_HPP_