#include "texture_manager.hpp"

#include "util/font/font.hpp"
#include "util/sdl_check.hpp"

SDL_Texture *TextureManager::Load(const std::string &fileName,
                                  const std::string &id,
                                  SDL_Renderer *pRenderer) {
  SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

  if (pTempSurface == nullptr) {
    std::cerr << IMG_GetError();
    return nullptr;
  }

  SDL_Texture *pTexture{
      SDL_CHECK(SDL_CreateTextureFromSurface(pRenderer, pTempSurface))};

  SDL_FreeSurface(pTempSurface);

  if (pTexture != nullptr) {
    m_textureMap[id] = pTexture;
    return pTexture;
  }

  return nullptr;
}

void TextureManager::LoadText(std::string const &fileName,
                              std::string const &textKey, std::string const &id,
                              SDL_Renderer *pRenderer) {
  Font font(pRenderer);
  font.Load(fileName);

  SDL_Texture *pTexture{
      SDL_CHECK(font.RenderText(textKey, 255, 255, 255, 255))};

  font.Unload();

  if (pTexture != nullptr) {
    m_textureMap[id] = pTexture;
  }
}

void TextureManager::draw(const std::string &id, int x, int y, int width,
                          int height, SDL_Renderer *pRenderer,
                          SDL_RendererFlip flip) {
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_CHECK(SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect,
                             0, nullptr, flip));
}

void TextureManager::drawFrame(const std::string &id, int x, int y, int width,
                               int height, int currentRow, int currentFrame,
                               SDL_Renderer *pRenderer, double angle, int alpha,
                               SDL_RendererFlip flip) {
  SDL_Rect srcRect;
  SDL_Rect destRect;
  srcRect.x = width * currentFrame;
  srcRect.y = height * currentRow;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
  SDL_CHECK(SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect,
                             angle, nullptr, flip));
}

void TextureManager::drawTile(const std::string &id, uint32_t margin,
                              uint32_t spacing, int x, int y, uint32_t width,
                              uint32_t height, uint32_t currentRow,
                              uint32_t currentFrame, SDL_RendererFlip flip,
                              SDL_Renderer *pRenderer) {
  SDL_Rect srcRect;
  SDL_Rect destRect;
  srcRect.x = margin + (spacing + width) * currentFrame;
  srcRect.y = margin + (spacing + height) * currentRow;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_CHECK(SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect,
                             0, nullptr, flip));
}

void TextureManager::clearTextureMap() { m_textureMap.clear(); }

void TextureManager::clearFromTextureMap(const std::string &id) {
  m_textureMap.erase(id);
}
