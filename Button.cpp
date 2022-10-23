#include "Button.h"
Button::Button()
{
    w = 0; h = 0;
    x = 0; y = 0;
    textureOffset = 0;
    isClick = false;
    helpTime = 0;
}

void Button::settings(SoundBuffer& s, Texture& t, Font& f, std::string str, int X, int Y, int W, int H, int offset)
{
    w = W; h = H;
    sb = s;
    sound.setBuffer(s);
    tx = t; font = f;
    x = X; y = Y;
    name = str;
    sp.setTexture(t);
    text.setFont(f);
    text.setPosition(x + 175 + offset, y + 20);
    text.setOutlineThickness(5);
    text.setOutlineColor(Color::Black);
    text.setCharacterSize(100);
    text.setString(str);
}

void Button::Click()
{
    isClick = true;
    sound.setVolume(Settings::GetVolume());
    sound.play();
}

void Button::update(const Vector2i& mousePos)
{
	if (sp.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		if (isClick)
		{
			helpTime += Timer::deltaTime();
			if (helpTime >= 0.1f)
			{
				isClick = false;
				textureOffset = 0;
				helpTime = 0;
			}
			textureOffset = 270;
		}
		else
			textureOffset = 135;
	}
    else {
        textureOffset = 0;
        isClick = false;
    }
    sp.setTextureRect({ 0, textureOffset, w, h });
}

Sprite Button::GetSprite()
{
    return sp;
}

std::string Button::GetText()
{
    return name;
}

void Button::draw(RenderWindow& window)
{
    sp.setPosition(x, y);
    window.draw(sp);
    window.draw(text);
}