#include "Cloud.h"

Cloud::Cloud()
{
    dx = rand() % 200 - 100;
    dy = rand() % 200 - 100;
    dx = dx == 0 ? 1 : dx;
    dy = dy == 0 ? 1 : dy;
    name = "cloud";
    tx.loadFromFile("assets/PixelElectroCloud.png");
    sp = Sprite(tx);
    sp.setColor(Color(255, 255, 255, 200));
}
void Cloud::update()
{
    x += dx * Timer::deltaTime();
    y += dy * Timer::deltaTime();

    if (x > W) x = 0;  if (x < 0) x = W;
    if (y > H) y = 0;  if (y < 0) y = H;
}