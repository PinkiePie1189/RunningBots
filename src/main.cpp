#include <texture.h>
#include<constants.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include<Map.h>
Texture *screen;

//const int RESOLUTION_W=1280,RESOLUTION_H=720,DISPLAY_MODE=0;

int main( int argc, char *args[] )
{
 ///Random
 srand((unsigned int)(time(NULL)));
 ///Random
 if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"SDL_Init() failed : %s ",SDL_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"SDL_Init() failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL failure",message,NULL);
     exit(-1);
    }
 if(TTF_Init()==-1)
    {
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"TTF_Init() failed : %s ",TTF_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"TTF_Init() failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL_TTF module failure",message,NULL);
     exit(-2);
    }
 bool MUSIC_MODULE_INIT=true;
 if(Mix_Init(MIX_INIT_MP3)&(MIX_INIT_MP3)!=MIX_INIT_MP3)
    {
     MUSIC_MODULE_INIT=false;
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"Mix_Init() failed : %s ",Mix_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"Mix_Init() failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL_mixer module failure",message,NULL);
    }

 Open_Window_and_Renderer(RESOLUTION_W,RESOLUTION_H,DISPLAY_MODE);
 screen=new Texture;
 screen->w=RESOLUTION_W;
 screen->h=RESOLUTION_H;
 screen->image=NULL;
 SCREEN=screen;
 if(screen==NULL)
    {
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"Open_Window_and_Renderer failed : %s ",SDL_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"Open_Window_and_Renderer failed : ");
     strcat(message,SDL_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL video module failure",message,NULL);
     exit(-1);
    }
 MUSIC_MODULE_INIT=true;
 if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1)
    {
     MUSIC_MODULE_INIT=false;
     FILE *log_file=fopen("err/logs.txt","w");
     fprintf(log_file,"Mix_OpenAudio failed : %s ",Mix_GetError());
     fclose(log_file);
     char message[TEXT_LENGTH_MAX];
     strcpy(message,"Mix_OpenAudio() failed : ");
     strcat(message,Mix_GetError());
     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"SDL_mixer module failure",message,NULL);
    }
 Flip_Buffers(screen);
 const int VOLUME=60;
 if(MUSIC_MODULE_INIT)
    {
     Mix_Volume(-1,MIX_MAX_VOLUME*VOLUME/100);
     Mix_Volume(2,MIX_MAX_VOLUME*VOLUME/100);
     Mix_Volume(3,MIX_MAX_VOLUME*(VOLUME/10)/100);
     Mix_Volume(4,MIX_MAX_VOLUME*(VOLUME/10)/100);
     Mix_VolumeMusic(MIX_MAX_VOLUME*VOLUME/100);
     //Mix_PlayMusic(launcher_background_music,-1);
     //Mix_FadeInMusic(launcher_background_music,-1,8000);
    }
 bool quit=false;
 SDL_Event ev;
 Map* harta=new Map("res/background.png","res/tile.png","res/level.map");
 while(!quit)
 {
     while(SDL_PollEvent(&ev))
     {
         if(ev.type==SDL_QUIT)
         {
             quit=true;
         }
     }
     harta->Draw(screen,0);
     Flip_Buffers(screen);

 }
 delete harta;
 return 0;
}
