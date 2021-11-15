#ifndef NEWGAME_INPUT_HANDLER_HPP
#define NEWGAME_INPUT_HANDLER_HPP

#include <SDL_events.h>

#include <cstdlib>
#include <cstring>
#include <entt/entity/fwd.hpp>
#include <iostream>

enum class ButtonState { ENone, EPressed, EReleased, EHeld };

class InputHandler {
 public:
  // Singleton.
  static InputHandler &Instance() {
    static InputHandler s_pInstance;
    return s_pInstance;
  }

  InputHandler(const InputHandler &) = delete;
  InputHandler &operator=(const InputHandler &) = delete;

  // Update and clean the input handler.
  void update(class GameStateMachine *);

  [[nodiscard]] ButtonState GetKeyState(SDL_Scancode keyCode) const;
  [[nodiscard]] bool GetKeyValue(SDL_Scancode keyCode) const;

  // Key Flags.
  ButtonState Dkey = ButtonState::ENone;
  ButtonState Akey = ButtonState::ENone;
  ButtonState SpaceKey = ButtonState::ENone;

 private:
  InputHandler() : mCurrState(SDL_GetKeyboardState(nullptr)) {
    memset(mPrevState, 0, SDL_NUM_SCANCODES);
  }

  ~InputHandler() { delete[] mPrevState; }

  // handle keyboard events
  void onKeyDownSym(const SDL_Event &event, class GameStateMachine *);
  void onKeyUpSym(const SDL_Event &event);

  // keyboard specific
  const Uint8 *mCurrState;
  Uint8 *mPrevState = new Uint8[SDL_NUM_SCANCODES];
};

#endif  // NEWGAME_INPUT_HANDLER_HPP
