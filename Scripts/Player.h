#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
    bool thrust;
    int textureX, textureY;
    float reload;
    int maxSpeed;
    float speed;
public:
    Player();
    void broke(bool);
    void SetTextureX(int);
    void SetTextureY(int);
    bool GetThrust();
    float GetAngle();
    float GetBoost();
    float GetReload();
    void SetAngle(float);
    void SetBoost(float);
    void SetReload(float);
    void update();
};

