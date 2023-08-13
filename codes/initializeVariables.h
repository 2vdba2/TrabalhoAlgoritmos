#ifndef INITIALIZEVARIABLES_H
#define INITIALIZEVARIABLES_H

#include "structs.h"
#include "constants.h"
#include <stdio.h>

void initializeIsaacEnemiesBullets(struct Enemy enemies[MAX_ENEMIES],struct Isaac *isaac,struct Bullet bullets[MAX_BULLLETS])
{
		for(int i = 0; i < MAX_BULLLETS; i++) {
			bullets[i].IsAlive = false;
		}

		//Characters Variables
		isaac->id='J';
		isaac->missionComplete=0;
		isaac->nLifes=300;
		isaac->nBombs=0;
		for(int i=0; i<MAX_ENEMIES; i++)
		{
			enemies[i].id='I';
		}
}

void initializeMapElement(struct MapElement mapElements[N_MAP_ELEMENTS])
{
	//This function define each mapElement value:
	
	int i;
	printf("initalize variables function");
	//BackGround
	i=MAP_ELEMENT_BACKGROUND_NUMBER;//0
	mapElements[i].id=' ';
	sprintf(mapElements[i].spritePath,"./Sprites/background.png");
	mapElements[i].canIsaacMove=1;
	mapElements[i].canEnemyMove=1;
	mapElements[i].isItInactiveBomb=0;
	mapElements[i].doesItDamageIsaac=0;
	mapElements[i].doesItDamageEnemy=0;


	//Wall
	i=1;
	mapElements[i].id='#';
	sprintf(mapElements[i].spritePath,"./Sprites/Wall.png");
	mapElements[i].canIsaacMove=0;
	mapElements[i].canEnemyMove=0;
	mapElements[i].isItInactiveBomb=0;
	mapElements[i].doesItDamageIsaac=0;
	mapElements[i].doesItDamageEnemy=0;

	


	//Fire
	i=MAP_ELEMENT_FIRE_NUMBER;//2
	mapElements[i].id='X';
	sprintf(mapElements[i].spritePath,"./Sprites/fire.png");
	mapElements[i].canIsaacMove=1;
	mapElements[i].canEnemyMove=1;
	mapElements[i].isItInactiveBomb=0;
	mapElements[i].doesItDamageIsaac=1;
	mapElements[i].doesItDamageEnemy=0;
	
	//Inactive Bomb
	i=3;
	mapElements[i].id='B';
	sprintf(mapElements[i].spritePath,"./Sprites/bombInactive.png");
	mapElements[i].canIsaacMove=1;
	mapElements[i].canEnemyMove=1;
	mapElements[i].isItInactiveBomb=1;
	mapElements[i].doesItDamageIsaac=0;
	mapElements[i].doesItDamageEnemy=0;

	//Active Bomb
	i=4;
	mapElements[i].id='b';
	sprintf(mapElements[i].spritePath,"./Sprites/bombActive.png");
	mapElements[i].canIsaacMove=0;
	mapElements[i].canEnemyMove=1;
	mapElements[i].isItInactiveBomb=0;
	mapElements[i].doesItDamageIsaac=0;
	mapElements[i].doesItDamageEnemy=1;

	//Portal
	i=MAP_ELEMENT_PORTAL_NUMBER; // 5
	mapElements[i].id='P';
	sprintf(mapElements[i].spritePath,"./Sprites/portal.png");
	mapElements[i].canIsaacMove=0;
	mapElements[i].canEnemyMove=0;
	mapElements[i].isItInactiveBomb=0;
	mapElements[i].doesItDamageIsaac=0;
	mapElements[i].doesItDamageEnemy=0;
	//Enemy
	i=MAP_ELEMENT_ENEMY_NUMBER;//6
	mapElements[i].id='I';
	sprintf(mapElements[i].spritePath,"./Sprites/enemy.png");
	mapElements[i].canIsaacMove=0;
	mapElements[i].canEnemyMove=0;
	mapElements[i].isItInactiveBomb=0;
	mapElements[i].doesItDamageIsaac=1;
	mapElements[i].doesItDamageEnemy=0;
	//BUllet
	i=7;
	mapElements[i].id='o';
	sprintf(mapElements[i].spritePath,"./Sprites/bullet.png");
	mapElements[i].canIsaacMove=0;
	mapElements[i].canEnemyMove=1;
	mapElements[i].isItInactiveBomb=0;
	mapElements[i].doesItDamageIsaac=0;
	mapElements[i].doesItDamageEnemy=1;


	//Isaac
	i=MAP_ELEMENT_ISAAC_NUMBER;//8
	mapElements[i].id='J';
	sprintf(mapElements[i].spritePath,"./Sprites/isaac.png");
	mapElements[i].canIsaacMove=1;
	mapElements[i].canEnemyMove=0;
	mapElements[i].isItInactiveBomb=0;
	mapElements[i].doesItDamageIsaac=0;
	mapElements[i].doesItDamageEnemy=0;
	
	for(int i=0;i<N_MAP_ELEMENTS;i++)
	{
		Image spriteImage = LoadImage(mapElements[i].spritePath);
		//ImageResize(&spriteImage, 25, 25);
		mapElements[i].sprite = LoadTextureFromImage(spriteImage);
	}
	
	godMode=0;

}

#endif
