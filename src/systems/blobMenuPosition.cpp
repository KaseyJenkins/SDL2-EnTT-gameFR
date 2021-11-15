#include "blobMenuPosition.hpp"

#include <entt/entity/registry.hpp>
#include <iostream>

#include "components/blobMenu.hpp"
#include "components/transform.hpp"
#include "core/game.hpp"
#include "tinytmx/tinytmx.hpp"
#include "util/gameStates/GameStateMachine.hpp"
#include "util/gameStates/MainMenuState.hpp"
#include "util/gameStates/PlayState.hpp"

void blobMenumovement(entt::registry &reg,
                      GameStateMachine *m_pGameStateMachine) {
  auto const view = reg.view<const BlobMenu, Transform>();

  // Get the key flags.
  ButtonState const d_key = InputHandler::Instance().Dkey;
  ButtonState const a_key = InputHandler::Instance().Akey;
  ButtonState const space_key = InputHandler::Instance().SpaceKey;

  for (auto const e : view) {
    auto &pos = view.get<Transform>(e).position2D;

    // D Key State.
    if (d_key == ButtonState::EPressed) {
      if (pos.y == 250) {
        pos.y = 290;
      } else {
        pos.y = 290;
      }
    }
    // A Key State.
    if (a_key == ButtonState::EPressed) {
      if (pos.y == 290) {
        pos.y = 250;
      } else {
        pos.y = 250;
      }
    }

    if (space_key == ButtonState::EPressed) {
      if (pos.y == 250) {
        m_pGameStateMachine->changeState(new PlayState());
      } else if (pos.y == 290) {
        Game::Instance().quit();
      }
    }
  }
}