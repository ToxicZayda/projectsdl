#include "enemy.h"
#include "hero.h"
#include "header.h"

Enemy init_enemy(int v, int x, int y)
{
    Enemy enemy;
    enemy.e = init_entity(x, y);
    enemy.e.sprite[0] = IMG_Load("mvt/r1.png");
    enemy.e.sprite[1] = IMG_Load("mvt/r2.png");
    enemy.e.sprite[2] = IMG_Load("mvt/r3.png");
    enemy.e.sprite[3] = IMG_Load("mvt/r4.png");
    enemy.e.sprite[4] = IMG_Load("mvt/flip.png");
    enemy.e.sprite[5] = IMG_Load("mvt/l1.png");
    enemy.e.sprite[6] = IMG_Load("mvt/l2.png");
    enemy.e.sprite[7] = IMG_Load("mvt/l3.png");
    enemy.e.sprite[8] = IMG_Load("mvt/l4.png");
    enemy.frame = 0;
    enemy.Edirection = 'l';
    enemy.vitesse = v;
    enemy.blocked = 0;
    enemy.min = 660;
    enemy.max = 2460;
    return enemy;
}
void aff_enemies(Enemies *enemies)
{
    int i;
    SDL_Rect pos;
    for(i = 0; i < enemies->nombre; i++)
    {
        pos = enemies->enemy[i].e.position;
        SDL_BlitSurface(enemies->enemy[i].e.sprite[enemies->enemy[i].frame], NULL, ecran, &pos);
        enemies->enemy[i].e.position.w = pos.w;
        enemies->enemy[i].e.position.h = pos.h;
    }
}
void free_enemy(Enemies *enemies)
{
    int i, j;
    for(j = 0; j < enemies->nombre; j++)
    {
        for(i = 0; i < 9; i++)
        {
            SDL_FreeSurface(enemies->enemy[j].e.sprite[i]);
        }
    }
}
void Deplacer(Enemies *enemies)
{
    int i;
    for(i = 0; i < enemies->nombre; i++)
    {
        enemies->enemy[i].e.position.x += decalage;
        enemies->enemy[i].min += decalage;
        enemies->enemy[i].max += decalage;
        if(enemies->enemy[i].e.position.x > enemies->enemy[i].max)
            enemies->enemy[i].Edirection = 'l';
        if (enemies->enemy[i].e.position.x <  enemies->enemy[i].min)
            enemies->enemy[i].Edirection = 'r';
        if(!enemies->enemy[i].blocked)
        {
            if(enemies->enemy[i].Edirection == 'r')
                enemies->enemy[i].e.position.x += enemies->enemy[i].vitesse;
            else
                enemies->enemy[i].e.position.x -= enemies->enemy[i].vitesse;
        }
    }
}

void collision_ennemy(Enemies *enemies)
{
    int i;
    for(i = 0; i < enemies->nombre; i++)
    {
        if(hero.frame != 9 && !((hero.e.position.x + hero.e.position.w < enemies->enemy[i].e.position.x) || (hero.e.position.x > enemies->enemy[i].e.position.x + enemies->enemy[i].e.position.w) ||
                                (hero.e.position.y + hero.e.position.h < enemies->enemy[i].e.position.y) || (hero.e.position.y > enemies->enemy[i].e.position.y + enemies->enemy[i].e.position.h )))
        {
            init_hero(&hero);
            background = init_back("back.png");
            enemies->enemy[0] = init_enemy(2, 660, 340);
            enemies->enemy[1] = init_enemy(2, 1560, 340);
            enemies->enemy[2] = init_enemy(2, 2460, 340);
            position_absolue =100;
        }
    }
}