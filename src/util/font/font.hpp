#ifndef UTIL_FONT_FONT_HPP_
#define UTIL_FONT_FONT_HPP_

#include <SDL_ttf.h>

#include <cstdint>
#include <string>
#include <unordered_map>

/// A Font class to encapsulate any font-specific functionality.

class Font {
 public:
  Font(class SDL_Renderer *);
  ~Font();

  // Load/unload from a file.
  bool Load(std::string const &fileName);
  void Unload();

  // Given string and this font, draw to a texture.
  class SDL_Texture *RenderText(std::string const &textKey, uint8_t r,
                                uint8_t g, uint8_t b, uint8_t a,
                                int pointSize = 30);

 private:
  // Map of point sizes to font data.
  std::unordered_map<int, TTF_Font *> mFontData;
  class SDL_Renderer *m_pRenderer;
};

#endif  // UTIL_FONT_FONT_HPP_