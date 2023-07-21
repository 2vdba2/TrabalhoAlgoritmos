#include "raylib.h"
#include <string.h>
#include "structs.h"

void Atirar(struct Bullet bullets[], int x, int y, int VelocityX, int VelocityY){
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
void AtualizarTiros(struct Bullet Bullets[], char map[30][60]) {
    for (int i = 0; i < 100; i++) {
        if (Bullets[i].IsAlive) {
            map[Bullets[i].posY][Bullets[i].posX] = ' ';
            if (map[Bullets[i].posY + Bullets[i].VelocityY][Bullets[i].posX + Bullets[i].VelocityX] == ' ') {
                map[Bullets[i].posY + Bullets[i].VelocityY][Bullets[i].posX + Bullets[i].VelocityX] = 'o';
                Bullets[i].posX += Bullets[i].VelocityX;
                Bullets[i].posY += Bullets[i].VelocityY;
            } else {
                Bullets[i].IsAlive = false;
            }
        }
    }
}
