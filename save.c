#include <stdio.h>
#include <stdlib.h>
#include "entity.h"
#include "hero.h"




void saveGame(Hero player, char filename[50],int save)
{
	if (save==1)
	{
	FILE *f = fopen(filename,"w");
	fprintf(f,"%d\n",player.e.position.x);
	fprintf(f,"%d\n",player.e.position.y);
	fclose(f);
	}
}

void LoadGame(Hero *player, char filename[50], int save)
{
<<<<<<< HEAD
	int x,y;
	if(save==2)
	{
	FILE *f = fopen(filename,"r");
	fscanf(f,"%d\n",&x);
	player->e.position.x=x;
	fscanf(f,"%d\n",&y);
	player->e.position.y=y;
=======
	if(save==2)
	{
	FILE *f = fopen(filename,"r");
	fscanf(f,"%d\n",&player->e.position.x);
	fscanf(f,"%d\n",&player->e.position.y);
>>>>>>> 210278e57bf2d969cb867f4a8a2f8693ea95ec09
	fclose(f);
	}
}

