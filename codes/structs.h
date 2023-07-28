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
    int vertex;
    char id;
    bool IsAlive;
};

struct Enemy
{
    int posX;
    int posY;
    int posXpx;
    int posYpx;
    int dx;
    int dy;
    char id;
    int vertex;
    bool IsAlive;
};

#endif
