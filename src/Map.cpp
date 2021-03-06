#include "Map.h"

Map::Map(char* path_to_background,char* path_to_tile,char* path_to_hole,char* path_to_config)
{
    //ctor
    bbackground_texture=Load_Transparent_Texture("res/background.png");
    background_texture=Load_Transparent_Texture(path_to_background);
    tile_texture=Load_Transparent_Texture(path_to_tile);
    hole_texture=Load_Transparent_Texture(path_to_hole);
    hole1_texture=Load_Transparent_Texture("res/hole1.png");
    LoadConfigFile(path_to_config);
}

Map::~Map()
{
    //dtor
}

void Map::Draw(Texture* _screen,int poz_min)
{
    Apply_Texture(0,0,bbackground_texture,_screen);
    first_tile=poz_min;
    last_tile=first_tile+(RESOLUTION_W/TILE_LENGTH)-1;
    int posx=0;
    for(int i=first_tile; i<=last_tile; i++)
    {
        if(map_configuration[i])
        {
            Apply_Texture(posx,RESOLUTION_H-TILE_LENGTH,background_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-2*TILE_LENGTH,tile_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-3*TILE_LENGTH,background_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-4*TILE_LENGTH,tile_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-5*TILE_LENGTH,background_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-6*TILE_LENGTH,tile_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-7*TILE_LENGTH,background_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-8*TILE_LENGTH,tile_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-9*TILE_LENGTH,background_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-10*TILE_LENGTH,tile_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-11*TILE_LENGTH,background_texture,_screen);
        }
        else
        {
            Apply_Texture(posx,RESOLUTION_H-TILE_LENGTH,hole1_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-2*TILE_LENGTH,hole_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-3*TILE_LENGTH,hole1_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-4*TILE_LENGTH,hole_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-5*TILE_LENGTH,hole1_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-6*TILE_LENGTH,hole_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-7*TILE_LENGTH,hole1_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-8*TILE_LENGTH,hole_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-9*TILE_LENGTH,hole1_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-10*TILE_LENGTH,hole_texture,_screen);
            Apply_Texture(posx,RESOLUTION_H-11*TILE_LENGTH,hole1_texture,_screen);
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

bool Map::Is_hole(int _pos)
{
 return !map_configuration[_pos];
}

int Map::Get_size()
{
 return map_configuration.size();
}
