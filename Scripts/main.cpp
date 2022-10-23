#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Menu.h"

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(W, H), "Air Strike!");
    Menu menu(window);
    Game game(window);

    while (window.isOpen())
    {
        Timer::tickUpdate();
        if(Settings::GetIsGameRunning())
        {
            game.run();
        }
        else
        {
            menu.run();
        }
    }
    return 0;
}
