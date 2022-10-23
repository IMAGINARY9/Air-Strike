#include "Bullet.h"
Bullet::Bullet()
{
    name = "bullet";
    tx.loadFromFile("assets/Bullets.png");
    sp = Sprite(tx);
}

void  Bullet::update()
{
    dx = cos(angle * DEGTORAD) * 1000;
    dy = sin(angle * DEGTORAD) * 1000;
    //angle+=rand()%7-3;  
    x += dx * Timer::deltaTime();
    y += dy * Timer::deltaTime();

    if (x > W || x<0 || y>H || y < 0) life = 0;
}