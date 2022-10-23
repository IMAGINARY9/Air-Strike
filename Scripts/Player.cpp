#include "Player.h"

Player::Player()
{
    name = "player";
    tx.loadFromFile("assets/Player.png");
    sp = Sprite(tx);
    textureX = 64;
    textureY = 0;
    reload = 0;
    life = 10;
    maxSpeed = 500;
}

void Player::broke(bool isWork)
{
    this->thrust = isWork;
}

void Player::SetTextureX(int textX)
{
    this->textureX = textX;
}
void Player::SetTextureY(int textY)
{
    this->textureY = textY;
}

bool Player::GetThrust() { return thrust; }
float Player::GetAngle() { return angle; }
float Player::GetBoost() { return boost; }
float Player::GetReload() { return reload; }

void Player::SetAngle(float value)
{
    angle = value;
}

void Player::SetBoost(float value)
{
    boost = value;
}

void Player::SetReload(float value)
{
    reload = value;
}

void Player::update()
{
    srand(time(0));
    if (thrust)
    {
        dx += cos(angle * DEGTORAD) * maxSpeed;
        dy += sin(angle * DEGTORAD) * maxSpeed;
    }
    else
    {
        dx *= 0.997;
        dy *= 0.997;
        angle += (rand() % 20 - 10) * 0.01f;
    }
    
    speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed)
    {
        dx *= maxSpeed / speed + boost;
        dy *= maxSpeed / speed + boost;
    }

    x += dx * Timer::deltaTime();
    y += dy * Timer::deltaTime();
    
    sp.setTextureRect({ textureX,textureY,64,64 });

    if (x > W) x = 0; if (x < 0) x = W;
    if (y > H) y = 0; if (y < 0) y = H;
}
