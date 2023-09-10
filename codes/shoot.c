#include "raylib.h"
#include <string.h>
#include "structs.h"
#include "constants.h"

// Function to shoot a bullet
void Shoot(struct Bullet bullets[], int x, int y, int VelocityX, int VelocityY) {
    // Find an available slot for a bullet
    int i = 0;
    while (bullets[i].IsAlive)
    {
        i++;
    }

    // Set bullet properties
    bullets[i].posX = x;
    bullets[i].posY = y;
    bullets[i].VelocityY = VelocityY;
    bullets[i].VelocityX = VelocityX;
    bullets[i].IsAlive = 1;
}


// Function to update bullets
void UpdateBullets(struct Bullet Bullets[], char map[][MAP_SIZE_X], struct Enemy enemies[], int* nEnemies) {
    for (int i = 0; i < MAX_BULLLETS; i++) {
        if (Bullets[i].IsAlive) {
            // Remove bullet from previous position on map
            if(map[Bullets[i].posY][Bullets[i].posX]!='J')
            {
                map[Bullets[i].posY][Bullets[i].posX] = ' ';
            }

            // Check if bullet can move to the new position
            if (map[Bullets[i].posY + Bullets[i].VelocityY][Bullets[i].posX + Bullets[i].VelocityX] == ' ') {
                // Update bullet's position on map
                map[Bullets[i].posY + Bullets[i].VelocityY][Bullets[i].posX + Bullets[i].VelocityX] = 'o';
                Bullets[i].posX += Bullets[i].VelocityX;
                Bullets[i].posY += Bullets[i].VelocityY;
            } 
            // Check if bullet hits an enemy
            else if(map[Bullets[i].posY + Bullets[i].VelocityY][Bullets[i].posX + Bullets[i].VelocityX] == 'I'){
                // Disable the bullet
                Bullets[i].IsAlive = false;
                
                // Apply damage to the enemy
                DamageEnemy((Bullets[i].posX + Bullets[i].VelocityX),(Bullets[i].posY + Bullets[i].VelocityY), enemies, nEnemies);
            } else {
                // Disable the bullet if it hits a wall or other obstacle
                Bullets[i].IsAlive = false;
            }
        }
    }
}

// Function to apply damage to an enemy
void DamageEnemy(int x, int y, struct Enemy enemies[], int nEnemies){
    for (int i = 0; i < nEnemies; i++) {
        if (enemies[i].posX == x && enemies[i].posY == y && enemies[i].IsAlive) {
            enemies[i].nLifes--;
            if(enemies[i].nLifes <= 0){
                enemies[i].IsAlive = false;
				// Update map if enemy is killed
				if(map[enemies[i].posY][enemies[i].posX] == enemies[i].id)
				{
					map[enemies[i].posY][enemies[i].posX]= ' ';
					enemies[i].id = ' ';
					EnemiesAlive--;
				}
            }
            break; 
        }
    }
}
