#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "Game.hpp"

class GameObject
{

private:
    int xObjPos;
    int yObjPos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;

public:
    GameObject( const char* textureSheet, int x, int y );
    ~GameObject();

    void update();
    void render();

};

#endif
