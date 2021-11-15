#include "font.hpp"

#include <iostream>
#include <vector>

#include "../sdl_check.hpp"

Font::Font(class SDL_Renderer *Renderer) : m_pRenderer(Renderer) {}

Font::~Font() {}

bool Font::Load(std::string const &fileName) {
  // We support these font sizes.
  std::vector<int> fontSizes = {8,  9,  10, 11, 12, 14, 16, 18, 20, 22,
                                24, 26, 28, 30, 32, 34, 36, 38, 40, 42,
                                44, 46, 48, 52, 56, 60, 64, 68, 72};

  for (auto const &size : fontSizes) {
    TTF_Font *font = TTF_OpenFont(fileName.c_str(), size);
    if (font == nullptr) {
      SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
      return false;
    }
    mFontData.emplace(size, font);
  }
  return true;
}

void Font::Unload() {
  for (auto &font : mFontData) {
    TTF_CloseFont(font.second);
  }
}

SDL_Texture *Font::RenderText(std::string const &textKey, uint8_t r, uint8_t g,
                              uint8_t b, uint8_t a, int pointSize) {
  // Convert to SDL_Color.
  SDL_Color sdlColor;
  sdlColor.r = r;
  sdlColor.g = g;
  sdlColor.b = b;
  sdlColor.a = a;

  // Find the font data for this point size.
  auto iter = mFontData.find(pointSize);
  if (iter != mFontData.end()) {
    TTF_Font *font = iter->second;
    std::string const actualText = textKey;
    // Draw this to a surface (blended for alpha)
    SDL_Surface *pTempSurface =
        TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
    if (pTempSurface != nullptr) {
      // Convert from surface to texture

      // Width and Height of the text surfaces.
      // std::cout << pTempSurface->w << std::endl;
      // std::cout << pTempSurface->h << std::endl;

      SDL_Texture *pTexture{
          SDL_CHECK(SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface))};

      SDL_FreeSurface(pTempSurface);

      if (pTexture != nullptr) {
        return pTexture;
      }
    }
  } else {
    SDL_Log("Point size %d is unsupported", pointSize);
  }

  return nullptr;
}