#ifndef MAP
#define MAP

#include <string>

class Map
{
private:
    std::string textureID;
    int mapScale;
    int tileSize;
    int scaledSize;

public:
    Map( std::string texID, int mapScl, int tileSz );
    ~Map();

    void loadMap( std::string path, int sizeX, int sizeY );
    void addTile( int srcX, int srcY, int x, int y);
};

#endif
