#include "level.h"

const int MAX_DISTANCE_BETWEEN_PLAYERS=19;

void Level::Clear()
{
 players[1].Clear();
 players[2].Clear();
}

void Level::Load()
{
 players[1].Load(1);
 players[2].Load(2);
 map=new Map("res/dirt.png","res/tile.png","res/hole.png","res/level.map");
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
 if(map->Is_hole(players[1].Get_pos()) && !players[1].Is_jumping())
    winner=2;
 if(map->Is_hole(players[2].Get_pos()) && !players[2].Is_jumping())
    winner=1;
 if(map->Is_hole(players[1].Get_pos()) && !players[1].Is_jumping() && map->Is_hole(players[2].Get_pos()) && !players[2].Is_jumping())
    winner=3;
 if(winner!=0)
    return winner;
 if(std::abs(players[1].Get_pos()-players[2].Get_pos())>MAX_DISTANCE_BETWEEN_PLAYERS)
    winner=std::max(players[1].Get_pos(),players[2].Get_pos())==players[1].Get_pos()?1:2;
 if(winner!=0)
    return winner;
 if(players[1].Get_pos()==map->Get_size())
    winner=1;
 if(players[2].Get_pos()==map->Get_size())
    winner=2;
 if(players[1].Get_pos()==map->Get_size() && players[2].Get_pos()==map->Get_size())
    winner=3;
 return winner;
}

void Level::Start(Texture *_screen)
{
 bool quit=false,plays=true;
 SDL_Event ev;
 Load();
 while(!quit)
 {
     while(plays && !quit)
        {
         while(SDL_PollEvent(&ev))
         {
             if(ev.type==SDL_QUIT || (ev.type==SDL_KEYDOWN && ev.key.keysym.scancode==SDL_SCANCODE_ESCAPE))
             {
                 quit=true;
             }
         }
         SDL_PumpEvents();
         Handle_Events();
         Print(_screen);
         Flip_Buffers(_screen);
         if(Get_winner()!=0)
            plays=false;
        }
    if(!quit)
       {
        int x=Finish_Screen(_screen);
        if(x==1)
           {
            Reset();
            plays=true;
            winner=0;
           }
        if(x==2)
           quit=true;
       }
 }
}

void Level::Reset()
{
 players[1].Reset();
 players[2].Reset();
}

int Level::Finish_Screen(Texture *_screen)
{
 TTF_Font *font=TTF_OpenFont("fonts/pixel.ttf",50);
 Texture *img;
 if(winner==1)
    img=Create_TTF_Texture(font,"PLAYER 1 WON!!",{255,0,0});
 if(winner==2)
    img=Create_TTF_Texture(font,"PLAYER 2 WON!!",{255,0,0});
 if(winner==3)
    img=Create_TTF_Texture(font,"NOBODY WON!",{255,0,0});
 Apply_Texture((RESOLUTION_W-img->w)/2,(RESOLUTION_H-img->h)/2,img,_screen);
 Destroy_Texture(img);
 img=Create_TTF_Texture(font,"Press ENTER to replay or press ESC to exit!",{0,0,255});
 Apply_Texture((RESOLUTION_W-img->w)/2,RESOLUTION_H-2*img->h,img,_screen);
 Destroy_Texture(img);
 Flip_Buffers(_screen);
 SDL_Delay(1000);
 SDL_Event ev;
 while(SDL_PollEvent(&ev));
 bool quit=false;
 while(!quit)
       {
        if(ev.type==SDL_KEYDOWN && (ev.key.keysym.scancode==SDL_SCANCODE_RETURN || ev.key.keysym.scancode==SDL_SCANCODE_ESCAPE))
           quit=true;
        SDL_PollEvent(&ev);
       }
 if(ev.key.keysym.scancode==SDL_SCANCODE_RETURN)
    return 1;
 else
    return 2;
}
