#pragma once
#include "Timer.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>

const float DEGTORAD = 0.017453f;

class Entity
{
protected:
    float x, y, dx, dy, R, angle, boost;
    int life;
    std::string name;
    Sprite sp;
    Texture tx;
public:
    Entity();
    float GetX();
    float GetY();
    float GetR();
    float GetAngle();
    float GetBoost();
    
    std::string GetName();
    int GetLife();


    void SetName(std::string);
    void SetLife(int);

    void settings(int X, int Y, float Angle = 0, int radius = 1, float boost = 0);

    virtual void update() {};
    virtual void broke(bool) {};

    void draw(RenderWindow& app);
    virtual ~Entity() {};
};