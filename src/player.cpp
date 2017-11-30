#include <player.h>

const int TILE_SIZE=64;
const int PLAYER_SIZE_W=64,PLAYER_SIZE_H=96;

void Player::Clear()
{
 Destroy_Texture(skin);
}

void Player::Load(int _id)
{
 id=_id;
 if(id==1)
    skin=Load_Transparent_Texture("res/player1.png");
 else
    skin=Load_Transparent_Texture("res/player2.png");
 cooldown.start();
}

void Player::Print(int x,int y,Texture *_screen)
{
 SDL_Rect image_pos;
 image_pos.w=PLAYER_SIZE_W;
 image_pos.h=PLAYER_SIZE_H;
 switch(state)
        {
         case 0: image_pos.x=0;
                 image_pos.y=0;
                 break;
         case 1: image_pos.x=PLAYER_SIZE_W;
                 image_pos.y=_state*PLAYER_SIZE_H;
                 break; //stang
         case 2: image_pos.x=2*PLAYER_SIZE_W;
                 image_pos.y=_state*PLAYER_SIZE_H;
                 break; //drept
         case 4: image_pos.x=0;
                 image_pos.y=PLAYER_SIZE_H;
                 break;
        }
 Apply_Texture(image_pos.x,image_pos.y,x,y,image_pos.w,image_pos.h,skin,_screen);
}

const int MOVEMENT_COOLDOWN=50,RUN_COOLDOWN=50,JUMP_COOLDOWN=300;

void Player::Handle_Events()
{
 if(cooldown.get_ticks()>=RUN_COOLDOWN && (state==1 || state==2) && _state==0)
    {
     _state++;
     pos++;
     return;
    }

 if(state==4 && cooldown.get_ticks()>=JUMP_COOLDOWN)
    {
     if(_state==0)
        _state=1,pos++;
     else
        state=0;
     cooldown.start();
     return;
    }
 if(state==4)
    return;

 if(((id==1 && keystates[SDL_SCANCODE_Q] && keystates[SDL_SCANCODE_W]) || (id==2 && keystates[SDL_SCANCODE_LEFTBRACKET] && keystates[SDL_SCANCODE_RIGHTBRACKET])))
    {
     if(cooldown.get_ticks()>=JUMP_COOLDOWN)
        {
         state=4;
         _state=0;
         pos++;
         cooldown.start();
        }
     return;
    }

 if(id==1)
    {
     if(cooldown.get_ticks()>=MOVEMENT_COOLDOWN)
        {
         if(keystates[SDL_SCANCODE_Q] || keystates[SDL_SCANCODE_W])
            {
             if((keystates[SDL_SCANCODE_Q]?1:2)!=state || state==0)
                {
                 state=(keystates[SDL_SCANCODE_Q]?1:2);
                 _state=0;
                 //pos++;
                 cooldown.start();
                }
            }
        }
    }
 else
    {
     if(cooldown.get_ticks()>=MOVEMENT_COOLDOWN)
        {
         if(keystates[SDL_SCANCODE_LEFTBRACKET] || keystates[SDL_SCANCODE_RIGHTBRACKET])
            {
             if((keystates[SDL_SCANCODE_LEFTBRACKET]?1:2)!=state || state==0)
                {
                 state=(keystates[SDL_SCANCODE_LEFTBRACKET]?1:2);
                 _state=0;
                 //pos++;
                 cooldown.start();
                }
            }
        }
    }
}

int Player::Get_pos()
{
 return pos;
}
