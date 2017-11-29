#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"

class Level
{
 private:
 Player players[3];
 int winner=0;

 public:
 void Clear();
 void Load();
 void Print(Texture *_screen);
 void Handle_Events();
 int Get_winner();
};

#endif // LEVEL_H
