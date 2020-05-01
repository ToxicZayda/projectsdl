#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include "entity.h"

typedef struct
{
    entity e;
    int frame,vitesse,max,min,blocked;
    char Edirection;
} Enemy;
typedef struct
{
    Enemy enemy[3];
    int nombre;
} Enemies;

Enemy init_enemy(int v,int x,int y);
void aff_enemies(Enemies *enemies);
void free_enemy(Enemies *enemies);
void Deplacer(Enemies *enemies);
void collision_ennemy(Enemies *enemies);

#endif 