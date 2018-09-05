#ifndef SPRITE_COMPONENT
#define SPRITE_COMPONENT

#include "SDL2/SDL.h"
#include "Components.hpp"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component
{
private:
    SDL_Rect srcRect;
    SDL_Rect destRect;
    SDL_Texture* texture;
    TransformComponent* transform;

    int frames = 0;
    int frameDelay = 100;
    bool isAnimated = false;

    int animIndx = 0;


public:

    std::map <const char*, Animation> animations;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    SpriteComponent( const char* path ) { setTexture( path ); }
    SpriteComponent( const char* path, bool isAnim ) {
	this->isAnimated = isAnim;

	Animation idle     = Animation ( 0, 7, 500 );
	Animation walkSide = Animation ( 1, 1, 1000 );
	Animation walkUp   = Animation ( 2, 1, 1000 );
	Animation walkDown = Animation ( 3, 1, 1000 );

	animations.emplace( "idle", idle );
	animations.emplace( "walkSideway", walkSide );
	animations.emplace( "walkUp", walkUp );
	animations.emplace( "walkDown", walkDown );

	play( "idle" );

	setTexture( path );
    }

    ~SpriteComponent() { SDL_DestroyTexture( this->texture ); }


    void setAnimIndx( int indx ) { this->animIndx = indx; }
    void setTexture ( const char* path ) { this->texture = TextureManager::LoadTexture( path ); }


    int getAnimIndx() { return this->animIndx; }


    void init() override {
	this->transform = &entity->getComponent< TransformComponent >();

	srcRect.x = srcRect.y = 0;
	srcRect.w = transform->getWidth();
	srcRect.h = transform->getHeight();
    }

    void update() override {

	if( this->isAnimated )
	    srcRect.x = srcRect.w * static_cast< int >( ( SDL_GetTicks() / frameDelay ) % frames );

	srcRect.y = animIndx * transform->getHeight();


	destRect.x = static_cast< int >( transform->getXPos() ) - Game::camera.x;
	destRect.y = static_cast< int >( transform->getYPos() ) - Game::camera.y;

	destRect.w = transform->getWidth() * transform->getScale();
	destRect.h = transform->getHeight() * transform->getScale();
    }
    void draw() override { TextureManager::Draw( texture, srcRect, destRect, spriteFlip ); }

    void play ( const char* animName ) {
	frames     = animations[ animName ].frames;
	animIndx   = animations[ animName ].index;
	frameDelay = animations[ animName ].delay;
    }
};

#endif
