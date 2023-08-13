#include "raylib.h"
#include <string.h>
#include "structs.h"
#include "constants.h"

void Atirar(struct Bullet bullets[], int x, int y, int VelocityX, int VelocityY) {
	int i = 0;
	while (bullets[i].IsAlive)
	{
		i++;
	}
	bullets[i].posX = x;
	bullets[i].posY = y;
	bullets[i].VelocityY = VelocityY;
	bullets[i].VelocityX = VelocityX;
	bullets[i].IsAlive = 1;

}
void AtualizarTiros(struct Bullet Bullets[], char map[][MAP_SIZE_X], struct Enemy enemies[], int* nEnemies) {
	for (int i = 0; i < MAX_BULLLETS; i++) {
		if (Bullets[i].IsAlive) {
			if(map[Bullets[i].posY][Bullets[i].posX]!='J')
			{
				map[Bullets[i].posY][Bullets[i].posX] = ' ';
			}
			if (map[Bullets[i].posY + Bullets[i].VelocityY][Bullets[i].posX + Bullets[i].VelocityX] == ' ') {
				map[Bullets[i].posY + Bullets[i].VelocityY][Bullets[i].posX + Bullets[i].VelocityX] = 'o';
				Bullets[i].posX += Bullets[i].VelocityX;
				Bullets[i].posY += Bullets[i].VelocityY;
			} else if(map[Bullets[i].posY + Bullets[i].VelocityY][Bullets[i].posX + Bullets[i].VelocityX] == 'I'){
				Bullets[i].IsAlive = false;
				
				DamageEnemy((Bullets[i].posX + Bullets[i].VelocityX),(Bullets[i].posY + Bullets[i].VelocityY), enemies, nEnemies);
			} else {
				Bullets[i].IsAlive = false;
			}
		}
	}
}
void DamageEnemy(int x, int y,struct Enemy enemies[], int nEnemies){
	for (int i = 0; i < nEnemies; i++) {
			if (enemies[i].posX == x && enemies[i].posY == y && enemies[i].IsAlive) {
					enemies[i].IsAlive = false;
					if(map[enemies[i].posY][enemies[i].posX] == enemies[i].id)
					{
						map[enemies[i].posY][enemies[i].posX]= ' ';
						enemies[i].id = ' ';
						EnemiesAlive--;
					}
					enemies[i].nLifes--;
					if(enemies[i].nLifes <= 0){
						enemies[i].IsAlive = false;
					}
				//break;
			}
		}
}
