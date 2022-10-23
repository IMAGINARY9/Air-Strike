#include "Explosion.h"

Explosion::Explosion()
{
    name = "explosion";
    tx.loadFromFile("assets/Explosion.png");
    sp = Sprite(tx);
    helpTime = 0;
    textureX = 0;
}

void Explosion::update()
{
    helpTime += Timer::deltaTime();
    if (helpTime >= 0.05f)
    {
        textureX += 64;
        helpTime = 0;
    }
    if (textureX >= 1024)
        life = 0;

    sp.setTextureRect({ textureX,0,64,64 });
}
