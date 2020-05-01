#include "header.h"

Background init_back(char background_name[])
{
    Background background;
    background.imageDeFond = IMG_Load(background_name);
    background.positionFond.x = 0;
    background.positionFond.y = 0;
    
    return background;
}
void  init_SDL()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load("tanit.png"), NULL);
    ecran = SDL_SetVideoMode(1280, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("The Call Of Justice", NULL);
    music = Mix_LoadMUS("catching-a-killer.mp3");
    Mix_PlayMusic(music, -1);

}
void aff_back(Background background)
{
    SDL_BlitSurface(background.imageDeFond, NULL, ecran, &background.positionFond);
}