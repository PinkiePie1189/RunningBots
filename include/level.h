#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "Map.h"

class Level
{
 private:
 Player players[3];
 Map *map;
 int winner=0;

 public:
 void Clear();
 void Load();
 void Print(Texture *_screen);
 void Handle_Events();
 int Get_winner();
 void Start(Texture *_screen);
 void Reset();
 int Finish_Screen(Texture *_screen);
};

#endif // LEVEL_H
