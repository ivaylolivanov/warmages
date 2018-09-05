#ifndef MAP
#define MAP

#include <string>

class Map
{
private:
    const char* mapFilePath;
    int mapScale;
    int tileSize;
    int scaledSize;

public:
    Map( const char* mapFilep, int mapScl, int tileSz );
    ~Map();

    void loadMap( std::string path, int sizeX, int sizeY );
    void addTile( int srcX, int srcY, int x, int y);
};

#endif
