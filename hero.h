#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED
#include "entity.h"
#include "header.h"
typedef struct 
{
	int  up, down, left, right;
}Mouvement;
typedef struct
{
    entity e;
    Mouvement mouvement;
    int frame, air, sol;
    char direction;
    int mouse_clicked, target, vitesse,Default_y;
} Hero;
Hero hero;
SDL_Surface *masque;
int intervalle1,intervalle2,destination,continuer,position_absolue;

void init_hero();
void aff_hero();
void getInput(SDL_Event event, int *continuer,Background *background);
void free_hero();
void doKeyUp(SDL_Event event);
void doKeyDown(SDL_Event event);
void mouvement_mouse();
void mouvement(SDL_Event event,Background *background);
SDL_Color GetPixel(int X, int Y);
int CollisionParfaite ();
#endif