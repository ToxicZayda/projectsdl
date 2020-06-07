#include "header.h"
#include "menu.h"
#include "hero.h"
#include "enemy.h"
#include "aEnigmes.h"
#include "Enigmes.h"

animated an;
int MenuP()
{

    int destination;
    TTF_Init();
    SDL_Surface *texte = NULL;
    SDL_Rect position;
    TTF_Font *police = NULL;
    SDL_Color couleur = {0, 0, 0};
    police = TTF_OpenFont("Ghost Writer - Demo.ttf", 30);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(police, "Copyright 2020 - Imperium ", couleur);
    position.x = 1000;
    position.y = 550;

    Menu m0 = init_menu("menu/menu.png", 4);
    //initialisation des boutons
    m0.B[0] = init_button(340, 200, "menu/play.png", "menu/play_active.png");
    m0.B[1] = init_button(340, 290, "menu/options.png", "menu/options_active.png");
    m0.B[2] = init_button(590, 200, "menu/credits.png", "menu/credits_active.png");
    m0.B[3] = init_button(590, 290, "menu/quit.png", "menu/quit_active.png");
    //iniinitialisation du SDL

    int continu = 1;
    //Affiche le menu
    //Affiche les boutons initials du menu
    init_animation(&an);
    SDL_Event even;


    while(continu)
    {
        aff_menu(&m0);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        aff_button(&m0);
        aff_animation(&an);
        //Gestion de l'input
        souris(even, &destination, &continu, &m0);
        SDL_Flip(ecran);
    }
    free_menu(&m0);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(texte);
    SDL_Flip(ecran);
    if(destination == 3 || destination == 0)
        free_animation(&an);
    return destination;
}
int MenuOp()
{
    int destination;
    TTF_Init();
    SDL_Surface *texte = NULL;
    SDL_Rect position;
    TTF_Font *police = NULL;
    SDL_Color couleur = {0, 0, 0};
    police = TTF_OpenFont("Ghost Writer - Demo.ttf", 30);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(police, "Copyright 2020 - Imperium ", couleur);
    position.x = 1000;
    position.y = 550;

    Menu m1 = init_menu("menu/menu.png", 2);

    //initialisation des boutons
    m1.B[0] = init_button(340, 200, "menu/sound.png", "menu/sound_active.png");
    m1.B[1] = init_button(590, 200, "menu/back.png", "menu/back_active.png");
    //iniinitialisation du SDL
    int continu = 1;
    //Affiche le menu
    //Affiche les boutons initials du menu
    SDL_Event even;
    while(continu)
    {
        aff_menu(&m1);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        aff_button(&m1);
        aff_animation(&an);
        //Gestion de l'input
        souris_MenuOp(even, &destination, &continu, &m1);
        SDL_Flip(ecran);
    }
    free_menu(&m1);
    SDL_Flip(ecran);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(texte);
    if(destination == 3 || destination == 0)
        free_animation(&an);
    return destination;
}
int Game()
{
    masque = NULL;
    Hero hero1;
    SDL_Rect positionMasque, pos [8];
    int X, Y;
    Uint32 couleur_obstacle;
    TTF_Init();
    positionMasque.x = 0;
    positionMasque.y = 0;
    masque = IMG_Load("mask.png");
    int activer_enigme = 0, exit, test, i, continu = 1, end, old, final = 0;
    //SDL_CloseAudio();
    Mix_FreeMusic(music);
    enigme E;
    Enemies enemies;
    enemies.nombre = 3;
    enemies.enemy[0] = init_enemy(20,660,340);
    enemies.enemy[1] = init_enemy(20,1560,340);
    enemies.enemy[2] = init_enemy(20,2460,340);
    background = init_back("back.png");
    intervalleH1 = 0, intervalleH2 = 0,intervalleE1 = 0, intervalleE2 = 0, decalage = 0, destination =  0, continuer = 1,position_absolue =100;
    init_hero(&hero1);
    SDL_Event event;
    SDL_EnableKeyRepeat(100, 100);

    while (continuer)
    {
        aff_back(background);
        aff_hero((&hero1));
        getInput(event, &continuer, &background,&hero1);
        collision_ennemy(&enemies,&hero1);
        Deplacer(&enemies);
        aff_enemies(&enemies);
        SDL_Flip(ecran);
        if(CollisionParfaite(hero1)!=0)
        {
            activer_enigme = 1;
            continuer = 0;
        }
    }

    if(activer_enigme)
    {
        E = initialiserEnigme("Enigmes/wEnigme/background.png", "Enigmes/wEnigme/win.png", "Enigmes/wEnigme/lose.png");
        afficherEnigme(&E);
        while(continu)
        {
            old = EndingCheck(&E);
            enigmeInput(&E, &continu);
            animationEnigme(&E, EndingCheck(&E), old);
            SDL_Flip(ecran);
            if (EndingCheck(&E) == 0)
            {
                exit = 0;
                continu = 0;
            }
            if(EndingCheck(&E) == -1)
            {
                exit = -1;
                continu = 0;
            }
        }
        if (exit == 0)
        {
            test = jEnigme();
            final = ending(&E, test);
        }
        if (exit == -1)
            final = ending(&E, exit);
        Mix_FreeChunk(E.backgroundMus);
        Mix_FreeChunk(E.rightEffect);
        Mix_FreeChunk(E.wrongEffect);
        Mix_FreeChunk(E.stampEffect);
        Mix_FreeChunk(E.houseAlarm);
        SDL_FreeSurface(E.background);
        SDL_FreeSurface(E.win);
        SDL_FreeSurface(E.lose);

        Mix_CloseAudio();
    }
    SDL_FreeSurface(background.imageDeFond);
    free_enemy(&enemies);
    free_hero(&hero1);
    SDL_FreeSurface(masque);
    TTF_Quit();
    SDL_FreeSurface(ecran);
    return destination;
}




