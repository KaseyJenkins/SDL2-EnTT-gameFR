#ifndef NEWGAME_TEXTURE_MANAGER_HPP
#define NEWGAME_TEXTURE_MANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <map>
#include <string>

class TextureManager {
 public:
  // Singleton.
  static TextureManager &Instance() {
    static TextureManager s_pInstance;
    return s_pInstance;
  }

  TextureManager(TextureManager const &) = delete;
  TextureManager &operator=(TextureManager const &) = delete;

  SDL_Texture *Load(std::string const &, std::string const &, SDL_Renderer *);
  void LoadText(std::string const &, std::string const &, std::string const &,
                SDL_Renderer *);

  void clearTextureMap();
  void clearFromTextureMap(std::string const &);

  void draw(std::string const &, int, int, int, int, SDL_Renderer *,
            SDL_RendererFlip flip = SDL_FLIP_NONE);
  void drawFrame(std::string const &, int, int, int, int, int, int,
                 SDL_Renderer *, double, int,
                 SDL_RendererFlip flip = SDL_FLIP_NONE);
  void drawTile(std::string const &id, uint32_t, uint32_t, int, int, uint32_t,
                uint32_t, uint32_t, uint32_t, SDL_RendererFlip, SDL_Renderer *);

  std::map<std::string, SDL_Texture *> const &getTextureMap() const {
    return m_textureMap;
  }

  // Experimental.
  std::map<std::string, SDL_Texture *> &getTextureMapDelete() {
    return m_textureMap;
  }

 private:
  TextureManager() = default;
  ~TextureManager() = default;

  std::map<std::string, SDL_Texture *> m_textureMap;
};

#endif  // NEWGAME_TEXTURE_MANAGER_HPP
