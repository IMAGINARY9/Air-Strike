#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Settings.h"
#include "Timer.h"
#include <string>

using namespace sf;

class Button
{
private:
    bool isClick;
    float helpTime;
    int w, h, x, y, textureOffset;
    SoundBuffer sb;
    Sound sound;
    Texture tx;
    Sprite sp;
    Font font;
    Text text;
    std::string name;
public:
    Button();
    void settings(SoundBuffer&, Texture&, Font&, std::string,int, int, int, int, int);
    void update(const Vector2i&);
    void draw(RenderWindow& window);
    Sprite GetSprite();
    std::string GetText();
    void Click();
};
