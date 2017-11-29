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
}

const int TILE_SIZE=64;
const int RESOLUTION_W=1280,RESOLUTION_H=720,DISPLAY_MODE=0;

void Level::Print(Texture *_screen)
{
 int pos_min=std::min(players[1].Get_pos(),players[2].Get_pos());
 players[1].Print(TILE_SIZE*(players[1].Get_pos()-pos_min),RESOLUTION_H-3*TILE_SIZE,_screen);
 players[2].Print(TILE_SIZE*(players[2].Get_pos()-pos_min),RESOLUTION_H-2*TILE_SIZE,_screen);
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
