#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
    Clock clock;
    bool thrust;
    bool fire;
    int textureX, textureY;
    float helpTime, tempAngle;
    float speed;
    int maxSpeed;
    float zoom, zoomAngle;
public:
    Entity* p;
    Enemy();
    Clock GetClock();
    void RestartClock();
    bool GetFire();
    void broke(bool);
    void update();
};

