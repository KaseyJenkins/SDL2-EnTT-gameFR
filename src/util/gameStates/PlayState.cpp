#include "PlayState.hpp"

#include <entt/entity/fwd.hpp>
#include <iostream>

#include "components/direction.hpp"
#include "components/enemy.hpp"
#include "components/player.hpp"
#include "components/state.hpp"
#include "components/texture.hpp"
#include "components/transform.hpp"
#include "core/factories.hpp"
#include "core/game.hpp"
#include "systems/enemySliderPosition.hpp"
#include "systems/enemySlimeRender.hpp"
#include "systems/movement.hpp"
#include "systems/render.hpp"
#include "systems/tileRender.hpp"
#include "tinytmx/tinytmx.hpp"
#include "util/camera.hpp"
#include "util/texture_manager.hpp"

namespace tinytmx {
class Map;
}

std::string const PlayState::s_playID = "PLAY";

void PlayState::logic(class Game *game) const {
  auto *tmxMap = game->getMap();
  auto &reg = game->getReg();
  auto *m_pGameStateMachine = game->getGameStateMachine();
  auto dt = game->getDT();

  enemySliderMovement(reg, dt);
  movement(reg, tmxMap, m_pGameStateMachine, dt);
}

void PlayState::render(class Game *game) const {
  auto *tmxMap = game->getMap();
  auto &reg = game->getReg();
  auto *m_pRenderer = game->getSDL_Renderer();

  TileLayerRendering(tmxMap, m_pRenderer);
  enemySlimeRender(reg, m_pRenderer);
  playerRender(reg, m_pRenderer);
}

bool PlayState::onEnter(Game *game) const {
  *(game->getMapPtr()) = new tinytmx::Map();
  game->getMap()->ParseFile("assets/maps/SecondLevel.tmx");
  game->LoadAllTilesets();

  auto &reg = game->getReg();
  auto *m_pRenderer = game->getSDL_Renderer();

  // Make the Enemy Slime.
  entt::entity const enemySlime = makeEnemy(reg);
  reg.get<Texture>(enemySlime).texture = TextureManager::Instance().Load(
      "assets/slime/Idle-Run (44x30).png", "idEnemy", m_pRenderer);
  reg.get<Texture>(enemySlime).srcRect = {0, 0, 44, 30};
  reg.get<Texture>(enemySlime).dstRect = {0, 0, 44, 30};
  reg.get<Transform>(enemySlime).position2D.x = 100;
  reg.get<Transform>(enemySlime).position2D.y = 386;

  // Make the Player.
  entt::entity const player = makePlayer(reg);
  reg.get<Texture>(player).texture = TextureManager::Instance().Load(
      "assets/virtualGuy/Idle-Run-Jump-Fall.png", "idPlayer", m_pRenderer);
  reg.get<Texture>(player).srcRect = {0, 0, 32, 32};
  reg.get<Texture>(player).dstRect = {0, 0, 32, 32};
  reg.get<Transform>(player).position2D.y = 160;

  // Initialize the camera to the Player's position.
  Camera::Instance().setTarget(&reg.get<Transform>(player).position2D);

  return true;
}

bool PlayState::onExit(Game *game) const {
  delete *(game->getMapPtr());
  *(game->getMapPtr()) = nullptr;

  // destroys all the entities in a range
  auto &reg = game->getReg();

  auto view = reg.view<Enemy, Texture, Transform, Direction>();
  reg.destroy(view.begin(), view.end());

  auto view1 = reg.view<Player, Texture, Transform, Direction, State>();
  reg.destroy(view1.begin(), view1.end());

  // Destroys the textures.
  auto &textureMap = TextureManager::Instance().getTextureMapDelete();
  SDL_DestroyTexture(textureMap["tileset"]);
  SDL_DestroyTexture(textureMap["idEnemy"]);
  SDL_DestroyTexture(textureMap["idPlayer"]);
  // TextureManager::Instance().clearFromTextureMap("tileset");
  // TextureManager::Instance().clearFromTextureMap("idEnemy");
  // TextureManager::Instance().clearFromTextureMap("idPlayer");

  return true;
}