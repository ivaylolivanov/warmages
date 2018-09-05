#ifndef ASSET_MANAGER
#define ASSET_MANAGER

#include <map>
#include <string>
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "ECSystem/EntityComponentSystem.hpp"

class AssetManager
{
private:
    std::map< std::string, SDL_Texture* > textures;
    Manager* manager;

public:
    AssetManager( Manager* mngr );
    ~AssetManager();

    void addTexture( std::string id, const char* path );
    SDL_Texture* getTexture( std::string id );
};

#endif
