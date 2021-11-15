#include "input_handler.hpp"

#include <SDL_events.h>

#include <entt/entity/registry.hpp>

#include "core/game.hpp"
#include "util/gameStates/GameStateMachine.hpp"
#include "util/gameStates/PlayState.hpp"

void InputHandler::update(GameStateMachine *gameStateMachine) {
  SDL_Event event;

  // Copy the previous keyboard state
  memcpy(mPrevState, mCurrState, SDL_NUM_SCANCODES);

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        Game::Instance().quit();
        break;
        //
        //            case SDL_JOYAXISMOTION:
        //                onJoystickAxisMove(event);
        //                break;
        //
        //            case SDL_JOYBUTTONDOWN:
        //                onJoystickButtonDown(event);
        //                break;
        //
        //            case SDL_JOYBUTTONUP:
        //                onJoystickButtonUp(event);
        //                break;
        //
        //            case SDL_MOUSEMOTION:
        //                onMouseMove(event);
        //                break;
        //
        //            case SDL_MOUSEBUTTONDOWN:
        //                onMouseButtonDown(event);
        //                break;
        //
        //            case SDL_MOUSEBUTTONUP:
        //                onMouseButtonUp(event);
        //                break;

      case SDL_KEYDOWN:
        onKeyDownSym(event, gameStateMachine);
        break;

      case SDL_KEYUP:
        onKeyUpSym(event);
        break;

      default:
        break;
    }
  }
}

void InputHandler::onKeyDownSym(const SDL_Event &event,
                                GameStateMachine *gameStateMachine) {
  if (GetKeyValue(SDL_SCANCODE_SPACE)) {
    if (GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::EPressed) {
      SpaceKey = ButtonState::EPressed;
    } else if (GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::EHeld) {
      SpaceKey = ButtonState::EHeld;
    }
  }

  if (GetKeyValue(SDL_SCANCODE_D)) {
    if (GetKeyState(SDL_SCANCODE_D) == ButtonState::EPressed) {
      Dkey = ButtonState::EPressed;
    } else if (GetKeyState(SDL_SCANCODE_D) == ButtonState::EHeld) {
      Dkey = ButtonState::EHeld;
    }
  }

  if (GetKeyValue(SDL_SCANCODE_A)) {
    if (GetKeyState(SDL_SCANCODE_A) == ButtonState::EPressed) {
      Akey = ButtonState::EPressed;
    } else if (GetKeyState(SDL_SCANCODE_A) == ButtonState::EHeld) {
      Akey = ButtonState::EHeld;
    }
  }
}

void InputHandler::onKeyUpSym(const SDL_Event &event) {
  if (GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::EReleased) {
    SpaceKey = ButtonState::EReleased;
  }

  if (GetKeyState((SDL_SCANCODE_D)) == ButtonState::EReleased) {
    Dkey = ButtonState::EReleased;
  }

  if (GetKeyState(SDL_SCANCODE_A) == ButtonState::EReleased) {
    Akey = ButtonState::EReleased;
  }
}

ButtonState InputHandler::GetKeyState(SDL_Scancode keyCode) const {
  if (mPrevState[keyCode] == 0) {
    if (mCurrState[keyCode] == 0) {
      return ButtonState::ENone;
    } else {
      return ButtonState::EPressed;
    }
  } else {
    if (mCurrState[keyCode] == 0) {
      return ButtonState::EReleased;
    } else {
      return ButtonState::EHeld;
    }
  }
}

bool InputHandler::GetKeyValue(SDL_Scancode keyCode) const {
  return mCurrState[keyCode] == 1;
}
