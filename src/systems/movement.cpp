#include "movement.hpp"

#include <cmath>
#include <entt/entity/registry.hpp>

#include "components/direction.hpp"
#include "components/player.hpp"
#include "components/state.hpp"
#include "components/transform.hpp"
#include "core/constants.hpp"
#include "core/game.hpp"
#include "tinytmx/tinytmx.hpp"
#include "util/dt.hpp"
#include "util/gameStates/GameStateMachine.hpp"
#include "util/gameStates/MainMenuState.hpp"
#include "util/gameStates/PlayState.hpp"

void movement(entt::registry &reg, tinytmx::Map *map,
              class GameStateMachine *m_pGameStateMachine, float dt) {
  const auto view = reg.view<const Player, Transform, Direction, State>();

  // The first layer is the only layer we directly interact with.
  const auto tileLayerInter = map->GetTileLayer(0)->GetDataTileFiniteMap();

  // Get the key flags.
  ButtonState d_key = InputHandler::Instance().Dkey;
  ButtonState a_key = InputHandler::Instance().Akey;
  ButtonState space_key = InputHandler::Instance().SpaceKey;

  for (const auto e : view) {
    auto &pos = view.get<Transform>(e).position2D;
    auto &vel = view.get<Transform>(e).velocity2D;

    auto &dir = view.get<Direction>(e).dir;

    // D Key State.
    if (d_key == ButtonState::EReleased && !Game::Instance().onTheGround) {
      if (vel.x > 0) {
        vel.x = 0;
      }
    } else if (d_key == ButtonState::EPressed &&
               (a_key == ButtonState::EReleased ||
                a_key == ButtonState::ENone)) {
      dir = Dir::RIGHT;
      vel.x = (Game::Instance().onTheGround ? 150.0f : 20.0f);
    } else if (d_key == ButtonState::EHeld &&
               (a_key == ButtonState::EReleased ||
                a_key == ButtonState::ENone) &&
               Game::Instance().onTheGround) {
      vel.x = 150.0f;
    }

    // A Key State.
    if (a_key == ButtonState::EReleased && !Game::Instance().onTheGround) {
      if (vel.x < 0) {
        vel.x = 0;
      }
    } else if (a_key == ButtonState::EPressed &&
               (d_key == ButtonState::EReleased ||
                d_key == ButtonState::ENone)) {
      dir = Dir::LEFT;
      vel.x = (Game::Instance().onTheGround ? -150.0f : -20.0f);
    } else if (a_key == ButtonState::EHeld &&
               (d_key == ButtonState::EReleased ||
                d_key == ButtonState::ENone) &&
               Game::Instance().onTheGround) {
      vel.x = -150.0f;
    }

    // Space Key State.
    if (space_key == ButtonState::EReleased) {
      if (vel.y < -120.0f) {
        vel.y = -120.0f;
      }
    } else if ((space_key == ButtonState::EPressed ||
                space_key == ButtonState::EHeld) &&
               Game::Instance().onTheGround) {
      vel.y = -300.0f;
    }

    // Drag
    if (Game::Instance().onTheGround && vel.x != 0) {
      vel.x += -10.0f * vel.x * dt;
      if (fabsf(vel.x) < 2.5f) {
        vel.x = 0.0f;
      }
    }

    // Previous position.
    float fPreviousPlayerPosX = pos.x;
    float fPreviousPlayerPosY = pos.y;

    vel.y += gravity * dt;

    pos.x += (vel.x * dt);
    pos.y += (vel.y * dt);

    // If the player went too far to the left or right.
    if (pos.x < 0) {
      // Move back
      pos.x = 0;
    } else if ((pos.x + 32 > LEVEL_WIDTH)) {
      pos.x = LEVEL_WIDTH - 32;
    }

    // If the player went too far up or down.
    if (pos.y < 0) {
      // Move back.
      pos.y = 0;
      // Hitting the ceiling.
      vel.y = 0;
    } else if ((pos.y + 32) > LEVEL_HEIGHT) {
      pos.y = LEVEL_HEIGHT - 32;

      // Falling into a pit gets you back to the Menu State.
      m_pGameStateMachine->changeState(new MainMenuState());
      return;
    }

    // Moving Left.
    if (vel.x < 0) {
      const auto tileRow =
          static_cast<int>((pos.x / map->GetTileset(0)->GetTileWidth()));

      int tileid1 = tileLayerInter->GetTileGid(
          tileRow,
          ((fPreviousPlayerPosY) / map->GetTileset(0)->GetTileWidth()));
      int tileid2 = tileLayerInter->GetTileGid(
          tileRow,
          ((fPreviousPlayerPosY + 31.9f) / map->GetTileset(0)->GetTileWidth()));

      if (tileid1 != 0 || tileid2 != 0) {
        pos.x = tileRow * 32 + 32;
      }  // Moving Right.
    } else if (vel.x > 0) {
      const auto tileRow =
          static_cast<int>(((pos.x + 32) / map->GetTileset(0)->GetTileWidth()));

      int tileid1 = tileLayerInter->GetTileGid(
          tileRow,
          ((fPreviousPlayerPosY) / map->GetTileset(0)->GetTileWidth()));
      int tileid2 = tileLayerInter->GetTileGid(
          tileRow,
          ((fPreviousPlayerPosY + 31.9f) / map->GetTileset(0)->GetTileWidth()));

      if (tileid1 != 0 || tileid2 != 0) {
        pos.x = tileRow * 32 - 32;
      }
    }

    Game::Instance().onTheGround = false;
    // Moving Up.
    if (vel.y < 0) {
      const auto tileColumn =
          static_cast<int>(((pos.y) / map->GetTileset(0)->GetTileWidth()));

      int tileid1 = tileLayerInter->GetTileGid(
          (pos.x / map->GetTileset(0)->GetTileWidth()), tileColumn);
      int tileid2 = tileLayerInter->GetTileGid(
          ((pos.x + 31.9f) / map->GetTileset(0)->GetTileWidth()), tileColumn);

      if (tileid1 != 0 || tileid2 != 0) {
        pos.y = tileColumn * 32 + 32;
        vel.y = 0;
      }  // Moving Down.
    } else if (vel.y > 0) {
      const auto tileColumn =
          static_cast<int>(((pos.y + 32) / map->GetTileset(0)->GetTileWidth()));

      int tileid1 = tileLayerInter->GetTileGid(
          (pos.x / map->GetTileset(0)->GetTileWidth()), tileColumn);
      int tileid2 = tileLayerInter->GetTileGid(
          ((pos.x + 31.9f) / map->GetTileset(0)->GetTileWidth()), tileColumn);

      if (tileid1 != 0 || tileid2 != 0) {
        pos.y = tileColumn * 32 - 32;
        vel.y = 0;
        Game::Instance().onTheGround = true;
      }
    }

    // Player State.

    if (vel.y == 0 && vel.x == 0) {
      view.get<State>(e).state = plState::IDLE;
    } else if (vel.y == 0 && vel.x != 0) {
      view.get<State>(e).state = plState::RUN;
    } else if (vel.y < 0) {
      view.get<State>(e).state = plState::JUMP;
    } else if (vel.y > 0) {
      view.get<State>(e).state = plState::FALL;
    }
  }
}
