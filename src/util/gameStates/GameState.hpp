#ifndef UTIL_GAMESTATE_HPP_
#define UTIL_GAMESTATE_HPP_

#include <entt/entity/fwd.hpp>
#include <string>

namespace tinytmx {
class Map;
}

class GameState {
 public:
  virtual ~GameState() = default;

  virtual void logic(class Game *) const = 0;
  virtual void render(class Game *) const = 0;

  virtual bool onEnter(class Game *) const = 0;
  virtual bool onExit(class Game *) const = 0;

  virtual std::string const &getStateID() const = 0;

 private:
};

#endif  // UTIL_GAMESTATE_HPP_