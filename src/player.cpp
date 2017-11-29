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
         case 0: image_pos.x=0; break;
         case 1: image_pos.x=PLAYER_SIZE_W; break; //stang
         case 2: image_pos.x=2*PLAYER_SIZE_W; break; //drept
        }
 Apply_Texture(image_pos.x,image_pos.y,x,y,image_pos.w,image_pos.h,skin,_screen);
}

const int MOVEMENT_COLDOWN=50;

void Player::Handle_Events()
{
 if(id==1)
    {
     if(cooldown.get_ticks()>=MOVEMENT_COLDOWN)
        {
         if(keystates[SDL_SCANCODE_Q] || keystates[SDL_SCANCODE_W])
            {
             if(state==0)
                state=keystates[SDL_SCANCODE_Q]?1:2;
             else
                {
                 //if(keystates[SDL_SCANCODE_Q] && keystates[SDL_SCANCODE_W])
                    //JUMP;
                 if((keystates[SDL_SCANCODE_Q]?1:2)!=state)
                    {
                     state=(keystates[SDL_SCANCODE_Q]?1:2);
                     pos++;
                     cooldown.start();
                    }
                }
            }
        }
    }
 else
    {
     if(cooldown.get_ticks()>=MOVEMENT_COLDOWN)
        {
         if(keystates[SDL_SCANCODE_LEFTBRACKET] || keystates[SDL_SCANCODE_RIGHTBRACKET])
            {
             if(state==0)
                state=keystates[SDL_SCANCODE_LEFTBRACKET]?1:2;
             else
                {
                 //if(keystates[SDL_SCANCODE_LEFTBRACKET] && keystates[SDL_SCANCODE_RIGHTBRACKET])
                    //JUMP;
                 if((keystates[SDL_SCANCODE_LEFTBRACKET]?1:2)!=state)
                    {
                     state=(!keystates[SDL_SCANCODE_LEFTBRACKET]?1:2);
                     pos++;
                     cooldown.start();
                    }
                }
            }
        }
    }
}

int Player::Get_pos()
{
 return pos;
}
