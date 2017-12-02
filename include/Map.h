#ifndef MAP_H
#define MAP_H
#define TILE_LENGTH 64
#include<texture.h>
#include<constants.h>
#include<vector>
#include<string>
class Map
{
    public:
        Map(char*path_to_background,char* path_to_tile,char* path_to_hole,char* path_to_config);
        virtual ~Map();
        void Draw(Texture* _screen,int poz_min);
        void LoadConfigFile(char* path_to_config);
        bool Is_hole(int _pos);
        int Get_size();
    protected:
    private:
        Texture* background_texture=NULL;
        Texture* tile_texture=NULL;
        Texture* bbackground_texture=NULL;
        Texture* hole_texture,*hole1_texture;
        std::vector<int> map_configuration;
        int first_tile,last_tile,totalTiles;
};

#endif // MAP_H
