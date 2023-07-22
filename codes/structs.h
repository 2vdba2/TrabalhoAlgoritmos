#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h> 
struct Bullet
{
    int posX;
    int posY;
    int VelocityY;
    int VelocityX;
    bool IsAlive;
};

struct Isaac
{
    int posX;
    int posY;
    int posXpx;
    int posYpx;
    int nBombs;
    int nLifes;
    bool IsAlive;
};

#endif
