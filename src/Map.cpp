#include "Map.h"

Map::Map(char* path_to_background,char* path_to_tile,char* path_to_config)
{
    //ctor
    background_texture=Load_Transparent_Texture(path_to_background);
    tile_texture=Load_Transparent_Texture(path_to_tile);
    LoadConfigFile(path_to_config);
}

Map::~Map()
{
    //dtor
}

void Map::Draw(Texture* _screen,int poz_min)
{
    Apply_Texture(0,0,background_texture,_screen);
    first_tile=poz_min;
    last_tile=first_tile+(RESOLUTION_W/TILE_LENGTH)-1;
    int posx=0;
    for(int i=first_tile; i<=last_tile; i++)
    {
        if(map_configuration[i])
        {
            Apply_Texture(posx,RESOLUTION_H-TILE_LENGTH,tile_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-2*TILE_LENGTH,tile_texture,_screen);
        }
        else
        {
            //display hole
        }
        posx+=TILE_LENGTH;
    }

}
void Map::LoadConfigFile(char* path_to_config)
{
    FILE*fin=fopen(path_to_config,"r");
    fscanf(fin,"%d",&totalTiles);
    for(int i=0; i<totalTiles; i++)
    {
        int x;
        fscanf(fin,"%d",&x);
        map_configuration.push_back(x);
    }
    fclose(fin);
}

