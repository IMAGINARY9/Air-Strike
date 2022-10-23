#include "Enemy.h"
#include <iostream>
Enemy::Enemy()
{
    thrust = true;
    name = "enemy";
    tx.loadFromFile("assets/Enemy.png");
    sp = Sprite(tx);
    textureX = 64;
    textureY = 0;
    helpTime = 0;
    tempAngle = angle;
    maxSpeed = 500;
    zoom = 300;
    zoomAngle = 30;
}
Clock Enemy::GetClock() { return clock; }
bool Enemy::GetFire() { return fire; }

void Enemy::broke(bool isWork)
{
    this->thrust = isWork;
}

void Enemy::RestartClock() 
{ 
    clock.restart(); 
}

void Enemy::update()
{
    srand(time(0));
    if (thrust)
    {
        textureY = 64;
        dx += cos(angle * DEGTORAD) * maxSpeed;
        dy += sin(angle * DEGTORAD) * maxSpeed;
    }
    else
    {
        textureY = 0;
        dx *= 0.997;
        dy *= 0.997;
    }

    speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed)
    {
        dx *= maxSpeed / speed + boost;
        dy *= maxSpeed / speed + boost;
    }

    x += dx * Timer::deltaTime();
    y += dy * Timer::deltaTime();
    angle += (rand() % 20 - 10) * 0.01f;

    
    helpTime += Timer::deltaTime();
    if (helpTime >= 0.3f)
    {
        tempAngle = angle;
        helpTime = 0;
    }
	if (tempAngle > angle) { textureX = 0; }
	else if (tempAngle < angle) { textureX = 128; }
	else { textureX = 64; }

    sp.setTextureRect({ textureX,textureY,64,64 });

    Vector2f distToPlayer(p->GetX() - x, p->GetY() - y);
    fire = distToPlayer.x * distToPlayer.x + distToPlayer.y * distToPlayer.y <= zoom * zoom;
    if (fire)
    {
        fire = zoomAngle >= fabs(atan2f(distToPlayer.x * dx + distToPlayer.y * dy, distToPlayer.x * dy - distToPlayer.y * dx) * 180 / 3.14159 - 90);
    }
    
    if (x > W) x = 0;  if (x < 0) x = W;
    if (y > H) y = 0;  if (y < 0) y = H;
}
