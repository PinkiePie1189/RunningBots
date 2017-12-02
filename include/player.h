#ifndef PLAYER_H
#define PLAYER_H

#include "texture.h"

class Player
{
 private:
 int id=0;
 Texture *skin=NULL;
 int state=0,_state=0;
 int pos=0;
 Timer cooldown;

 public:
 void Clear();
 void Load(int _id);
 void Print(int x,int y,Texture *_screen);
 void Handle_Events();
 int Get_pos();
 bool Is_jumping();
 void Reset();
};

#endif // PLAYER_H
