#include "level.h"

void Level::Clear()
{
 players[1].Clear();
 players[2].Clear();
}

void Level::Load()
{
 players[1].Load(1);
 players[2].Load(2);
 map=new Map("res/dirt.png","res/tile.png","res/level.map");
}

void Level::Print(Texture *_screen)
{
 int pos_min=std::min(players[1].Get_pos(),players[2].Get_pos());
 map->Draw(_screen,pos_min);
 players[1].Print(TILE_LENGTH*(players[1].Get_pos()-pos_min),RESOLUTION_H-5*TILE_LENGTH,_screen);
 players[2].Print(TILE_LENGTH*(players[2].Get_pos()-pos_min),RESOLUTION_H-3*TILE_LENGTH,_screen);
}

void Level::Handle_Events()
{
 players[1].Handle_Events();
 players[2].Handle_Events();
}

int Level::Get_winner()
{
 return 0;
}
