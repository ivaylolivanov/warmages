#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include "Game.hpp"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture( const char* filename );
    static void Draw ( SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flipFlag );
};

#endif
