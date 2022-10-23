#include "Entity.h"
Entity::Entity()
{
    life = 1;
    x = 0;
    y = 0;
    angle = 0;
    R = 1;
}

float Entity::GetX()
{
	return x;
}
float Entity::GetY()
{
	return y;
}
float Entity::GetR()
{
	return R;
}
float Entity::GetAngle()
{
	return angle;
}
float Entity::GetBoost()
{
	return boost;
}

std::string Entity::GetName()
{
	return name;
}
int Entity::GetLife()
{
	return life;
}

void Entity::SetName(std::string name)
{
    this->name = name;
}
void Entity::SetLife(int value)
{
    life = value;
}
void Entity::settings(int X, int Y, float Angle, int radius, float B)
{
    x = X; y = Y;
    angle = Angle;
    R = radius;
    boost = B;
}

void Entity::draw(RenderWindow& window)
{
    sp.setRotation(angle + 90);
    sp.setPosition(x, y);
    sp.setOrigin(R, R);
    window.draw(sp);


    CircleShape circle(R);
    circle.setFillColor(Color(255, 0, 0, 170));
    circle.setPosition(x, y);
    circle.setOrigin(R, R);
    //app.draw(circle);
}