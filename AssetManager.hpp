#ifndef ASSET_MANAGER
#define ASSET_MANAGER

#include <map>
#include <string>
#include "Vector2D.hpp"
#include "TextureManager.hpp"

#ifdef _WIN32

#include "ECSystem\EntityComponentSystem.hpp"

#endif



#ifdef _WIN64

#include "ECSystem\EntityComponentSystem.hpp"

#endif



#ifdef __linux__

#include "ECSystem/EntityComponentSystem.hpp"

#endif



class AssetManager
{
private:
    Manager* manager;
    std::map< std::string, SDL_Texture* > textures;

public:
    AssetManager( Manager* mngr );
    ~AssetManager();

    // Game ojbects management
    void createProjectile( Vector2D pos, Vector2D vel, int range, int speed, std::string id );
    void createGameObject( Vector2D pos, bool stat, int scl, int durability, int mass, std::string id );

    // Texture management
    void addTexture( std::string id, const char* path );
    SDL_Texture* getTexture( std::string id );
};

#endif
