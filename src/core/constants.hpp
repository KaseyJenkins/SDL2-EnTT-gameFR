#ifndef NEWGAME_CONSTANTS_HPP
#define NEWGAME_CONSTANTS_HPP

#include "util/pos.hpp"

// The width and height of the map in tiles.
constexpr Pos tiles = {20, 15};
// The pixel size of tiles.
constexpr int tileSize = 32;
// The width and height of the map in pixels.
constexpr Pos tilesPx = tiles * tileSize;

// Frame rate.
constexpr int fps = 25;

constexpr float gravity = 250.0f;

// The dimensions of the level.
constexpr int LEVEL_WIDTH = 3200;
constexpr int LEVEL_HEIGHT = 480;

// Screen dimension constants.
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

#endif  // NEWGAME_CONSTANTS_HPP
