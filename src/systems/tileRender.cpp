#include "tileRender.hpp"

#include <SDL_render.h>

#include "core/constants.hpp"
#include "tinytmx/tinytmx.hpp"
#include "util/camera.hpp"
#include "util/texture_manager.hpp"

void TileLayerRendering(tinytmx::Map *tmxMap, SDL_Renderer *m_pRenderer) {
  float fCameraPosX = Camera::Instance().getPosition().x;
  float fCameraPosY = Camera::Instance().getPosition().y;

  int x = 0;
  int y = 0;
  int x2 = 0;
  int y2 = 0;

  x = static_cast<int>((fCameraPosX / 32));
  y = static_cast<int>((fCameraPosY / 32));

  x2 = int(fCameraPosX) % 32;
  y2 = int(fCameraPosY) % 32;

  const auto &m_tileSize = tmxMap->GetTileWidth();
  const auto &m_numRows = tiles.y;
  const auto &m_numColumns = tiles.x;

  // Loop through all Tile Layers and draw them.
  for (int ii = 0; ii < tmxMap->GetNumTileLayers(); ++ii) {
    for (int i = 0; i < m_numRows; i++) {
      for (int j = 0; j < m_numColumns + 1; j++) {
        // Prevent out-of-bound access.
        if ((j + x) >= tmxMap->GetWidth() || (i + y) >= tmxMap->GetHeight()) {
          std::cout << "Too far gone!" << std::endl;
          continue;
        }

        const auto &gid =
            tmxMap->GetTileLayer(ii)->GetDataTileFiniteMap()->GetTileGid(j + x,
                                                                         i + y);

        if (gid == 0) {
          continue;
        }

        // Check whether the tile is flipped.
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (tmxMap->GetTileLayer(ii)
                ->GetDataTileFiniteMap()
                ->IsTileFlippedHorizontally(j + x, i + y)) {
          flip = SDL_FLIP_HORIZONTAL;
        } else if (tmxMap->GetTileLayer(ii)
                       ->GetDataTileFiniteMap()
                       ->IsTileFlippedVertically(j + x, i + y)) {
          flip = SDL_FLIP_VERTICAL;
        }

        const auto &tilesetIndex = tmxMap->GetTileLayer(ii)
                                       ->GetDataTileFiniteMap()
                                       ->GetTileTilesetIndex(j + x, i + y);
        const auto tileset = tmxMap->GetTileset(tilesetIndex);
        // Draw a tile.
        TextureManager::Instance().drawTile(
            tileset->GetName(), tileset->GetMargin(), tileset->GetSpacing(),
            ((j * m_tileSize) - x2), ((i * m_tileSize) - y2), m_tileSize,
            m_tileSize, ((gid - 1) / tileset->GetColumns()),
            ((gid - 1) % tileset->GetColumns()), flip, m_pRenderer);
      }
    }
  }
}
