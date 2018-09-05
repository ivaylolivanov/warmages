#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject( const char* textureSheet, int x, int y )
{
    objTexture = TextureManager::LoadTexture( textureSheet );

    xObjPos = x;
    yObjPos = y;
}

void GameObject::update()
{
    xObjPos++;
    yObjPos++;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xObjPos;
    destRect.y = yObjPos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::render()
{
    SDL_RenderCopy( Game::renderer, objTexture, &srcRect, &destRect);
}
