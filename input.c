#include "hero.h"
#include "sdl.h"

//Fonction qui gère l'animation de l'héro en changeant de frame
void Animation_Personnage(Hero *hero)
{
    char direction;

    if(!hero->air && !hero->mouvement.up && hero->frame != 9)
        hero->frame++;

    if (hero->mouvement.left)
    {
        if(hero->frame <= 4 || hero->frame >= 9)
            hero->frame = 5;
        direction = 'l';
    }
    if (hero->mouvement.right )
    {
        if(hero->frame >= 4)
            hero->frame = 0;
        direction = 'r';
    }

    if(direction != 'r' && direction != 'l')
        direction = hero->direction;

    if(hero->direction != direction && !hero->air )
    {
        hero->frame = 4;
        hero->direction = direction;
    }

}
SDL_Color GetPixel(int X, int Y)
{
    SDL_Color color;
    Uint32 col = 0;
    char *pPosition = (char * ) masque->pixels;
    pPosition += (masque->pitch * Y);

    pPosition += (masque->format->BytesPerPixel * X);
    memcpy(&col, pPosition, masque->format->BytesPerPixel);

    SDL_GetRGB(col, masque->format, &color.r, &color.g, &color.b);
    return (color);
}


int CollisionParfaite (Hero hero)
{
    SDL_Rect pos [1] ;
    int W, H, X, Y, i, collision;

    SDL_Color couleur_obstacle, color;

    couleur_obstacle.r = 119;
    couleur_obstacle.g = 9;
    couleur_obstacle.b = 120;


    X = hero.e.position.x;
    Y = hero.e.position.y;
    W = hero.e.position.w;
    H = hero.e.position.h; // intialiser position



    /* pos[0].x = X;
     pos[0].y = Y;


     pos[1].x = X + W / 2;
     pos[1].y = Y;


     pos[2].x = X + W;
     pos[2].y = Y;


     pos[3].x = X ;
     pos[3].y = Y + H / 2;


     pos[4].x = X;
     pos[4].y = Y + H;


     pos[5].x = X + W / 2;
     pos[5].y = Y + H;


     pos[6].x = X + W;
     pos[6].y = Y + H;


     pos[7].x = X + W;
     pos[7].y = Y + H / 2; // initialiser les 8 pos*/
    pos[0].x = X + W;
    pos[0].y = Y + H / 2;



    collision = 0;


    for  (i = 0; i < 1; i++)

    {
        color = GetPixel (pos[i].x, pos[i].y);
        if (couleur_obstacle.r == color.r && couleur_obstacle.g == color.g && couleur_obstacle.b == color.b)
            collision = 1;
    }

    return (collision);

}

//Fonction qui permet de déplacer l'héro
void Deplacer_Hero(int vitesse, Hero *hero)
{
    hero->e.position.x += vitesse;
    position_absolue += vitesse;
}

//Fonction qui permet le scrolling du background quand l'héro atteint la moitié de l'écran
void scrolling(Background *background, int vitesse)
{
    background->positionFond.x += vitesse;
    position_absolue -= vitesse;
    decalage = vitesse;
}

//Fonction qui assure l'alternance entre scrolling et déplacement de l'héro
void mouvement(SDL_Event event, Background *background, Hero *hero)
{
    intervalleH2 = SDL_GetTicks();
    decalage = 0;
    SDLKey key = event.key.keysym.sym;
    if((key == SDLK_UP || key == SDLK_LEFT || key == SDLK_RIGHT || (hero->mouse_clicked )) && intervalleH2 - intervalleH1 > 100)
    {
        intervalleH1 = intervalleH2;
        Animation_Personnage(hero);
        CollisionParfaite((*hero));

        if (hero->mouvement.left)
        {
            if(hero->e.position.x >= 640 || background->positionFond.x >= 0)
                Deplacer_Hero(-hero->vitesse, hero);

            else
                scrolling(background, hero->vitesse);
        }
        if (hero->mouvement.right)
        {
            if(hero->e.position.x <= 640 || background->positionFond.x <= (1280 - 3150) + 20)
            {
                if(hero->e.position.x + hero->e.position.w < 1280 - (60))
                    Deplacer_Hero(hero->vitesse, hero);
            }
            else
                scrolling(background, -hero->vitesse);
        }
    }
}

//Fonction de saut de l'héro
void jump(SDL_Event event, Hero *hero)
{
    if(hero->frame != 9)
    {
        if(hero->air && hero->e.position.y > JumpLimit && !hero->sol)
            hero->e.position.y += Gravity;
        if(hero->e.position.y <= JumpLimit )
            hero->sol = 1;
        if(hero->e.position.y < Hero_Default_Y && hero->sol )
            hero->e.position.y -= Gravity;
        if(hero->e.position.y == Hero_Default_Y)
        {
            hero->sol = 0;
            hero->air = 0;
        }
    }
}

//Fonction qui déclenche le mouvement quand la touché est appuyée
void doKeyDown(SDL_Event event, Hero *hero)
{
    if(event.key.keysym.sym != SDLK_DOWN &&  hero->e.position.y != Hero_Default_Y && !hero->air && (event.key.keysym.sym != SDLK_UP))
        hero->e.position.y = Hero_Default_Y;
    if ((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_SPACE ))
    {
        if(hero->frame != 9)
        {
            hero->mouvement.up = 1;
            hero->air = 1;
        }
    }
    if (event.key.keysym.sym == SDLK_DOWN && !hero->air && !hero->sol)
    {
        hero->mouse_clicked = 0;
        hero->frame = 9;
        hero->e.position.y = 250;
    }

    if (event.key.keysym.sym == SDLK_LEFT)
    {
        hero->mouvement.left = 1;
        hero->mouvement.right = 0;
        hero->mouse_clicked = 0;
    }

    if (event.key.keysym.sym == SDLK_RIGHT )
    {
        hero->mouvement.right = 1;
        hero->mouvement.left = 0;
        hero->mouse_clicked = 0;
    }
}

//Fonction qui désenclenche le mouvement quand la touché n'est plus appuyée
void doKeyUp(SDL_Event event, Hero *hero)
{
    if ((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_SPACE))
    {
        if(hero->frame != 9)
            hero->mouvement.up = 0;
    }

    if (event.key.keysym.sym == SDLK_LEFT)
    {
        hero->mouvement.left = 0;
        hero->frame = 5;
    }

    if (event.key.keysym.sym == SDLK_RIGHT)
    {
        hero->mouvement.right = 0;
        hero->frame = 0;
    }
}

//Fonction permettant le mouvement avec la souris
void mouvement_mouse(Hero *hero)
{
    if(hero->mouse_clicked )
    {
        if(hero->mouvement.right && hero->target < hero->e.position.x)
        {
            hero->mouse_clicked = 0;
            hero->mouvement.right = 0;
        }
        if(hero->mouvement.left && hero->target > hero->e.position.x)
        {
            hero->mouvement.left = 0;
            hero->mouse_clicked = 0;
        }
    }
}

//Fonction qui augmente la vitesse de l'hero en appuyant sur Shift (gauche)
void Acceleration(Hero *hero, int acceleration)
{
    hero->vitesse += acceleration;
}

//Fonction qui gère l'input du joueur
void getInput(SDL_Event event, int *continuer, Background *background, Hero *hero)
{
    int i;
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        (*continuer) = 0;
        break;
    case SDL_KEYDOWN:
        doKeyDown(event, hero);
        switch(event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            (*continuer) = 0;
            break;
        case SDLK_LSHIFT:
            Acceleration(hero, 15);
        }
        break;
    case SDL_KEYUP:
        doKeyUp(event, hero);
        switch(event.key.keysym.sym)
        {
        case SDLK_LSHIFT:
            Acceleration(hero, -15);
        }
        break;
    case SDL_MOUSEBUTTONUP:
        hero->target = event.button.x;
        hero->mouse_clicked = 1;
        if(hero->target > hero->e.position.x)
            hero->mouvement.right = 1;
        else
            hero->mouvement.left = 1;
        break;
    }
    mouvement_mouse(hero);
    mouvement(event, background, hero);
    jump(event, hero);
}
