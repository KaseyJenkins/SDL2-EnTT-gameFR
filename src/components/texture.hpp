#ifndef NEWGAME_TEXTURE_HPP
#define NEWGAME_TEXTURE_HPP

#include <SDL.h>

class Texture {
public:

    SDL_Texture* texture;

    SDL_Rect srcRect;
    SDL_Rect dstRect;

    double angle;
};

#endif //NEWGAME_TEXTURE_HPP
