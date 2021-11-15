#ifndef UTIL_PLAYSTATE_HPP_
#define UTIL_PLAYSTATE_HPP_

#include <entt/entity/fwd.hpp>

#include "GameState.hpp"

namespace tinytmx {
class Map;
}

class PlayState : public GameState {
 public:
  void logic(class Game *) const override;
  void render(class Game *) const override;

  bool onEnter(class Game *) const override;
  bool onExit(class Game *) const override;

  std::string const &getStateID() const override { return s_playID; }

 private:
  static std::string const s_playID;
};

#endif  // UTIL_PLAYSTATE_HPP_