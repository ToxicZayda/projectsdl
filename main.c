#include "header.h"

int main(int argc, char *argv[])
{
    
    init_SDL();
    int continuer=1,choix=3;

    while(continuer)
    {
        switch(choix)
        {
            case 0:
            continuer=0;
            break;
            case 1:
            choix = MenuP();
            break;
            case 2:
            choix = MenuOp();
            break;
            case 3:
            choix = Game();
            break;
        }
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}