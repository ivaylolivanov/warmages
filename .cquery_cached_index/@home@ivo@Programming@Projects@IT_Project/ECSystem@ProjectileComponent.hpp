#ifndef PROJECTILE_COMPONENT
#define PROJECTILE_COMPONENT

#ifdef _WIN32

#include "..\Vector2D.hpp"

#endif



#ifdef _WIN64

#include "..\Vector2D.hpp"

#endif



#ifdef __linux__

#include "../Vector2D.hpp"

#endif


#include "Components.hpp"
#include "EntityComponentSystem.hpp"

class ProjectileComponent : public Component
{
private:
    TransformComponent* transform;
    int range    = 0;
    int speed    = 0;
    int distance = 0;
    Vector2D velocity;

public:
    ProjectileComponent( int rng, int spd, Vector2D vel ) : range( rng ), speed( spd ), velocity( vel ){}
    ~ProjectileComponent(){}

    void init() override {
	transform = &entity->getComponent< TransformComponent >();
	transform->setVelocity( this->velocity );
	transform->setAcceleration( 7.0f );
	transform->setStep( 1.0f );
    }

    void update() override {
	distance += speed;

	if( distance > range )
	{
	    printf("Out of range\n");
	    entity->destroy();
	}
	else if( transform->getXPos() > Game::camera.x + Game::camera.w ||
		 transform->getXPos() < Game::camera.x ||
		 transform->getYPos() > Game::camera.y + Game::camera.h ||
		 transform->getYPos() < Game::camera.y )
	{
	    printf("Out of bounds\n");
	    entity->destroy();
	}
    }

};

#endif
