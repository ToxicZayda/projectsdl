#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include "sdl.h"

typedef struct
{
    SDL_Surface *imageDeFond ;
    SDL_Rect positionFond;

} Background;

Background background;

int MenuController();
int MenuLoad(int *save);
int MenuMultiplayer();
int Game(int *save);
int MenuOp();
int MenuP();
Background init_back(char background_name[]);
void init_SDL();
void aff_back(Background background);
int level1();
int level2();
#endif // HEADER_H_INCLUDED
