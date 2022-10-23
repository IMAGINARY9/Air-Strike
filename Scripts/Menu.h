#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Settings.h"
#include "Button.h"
#include "Timer.h"
#include <iostream>
#include <list>

using namespace std;

class Menu
{
public:
	Menu(RenderWindow&);
	void run();
private:
	bool isSettings;
	RenderWindow& window;
	Vector2i mousePos;
	Texture bg, bg2, btn, sbtn, mbtn;
	Font font;
	Text volumeText;
	list<Button*> menuButtons;
	list<Button*> settingsButtons;
	Sprite background, background2;
	SoundBuffer ClkBf;
	Music music;

	void Render();
	void MusicUpdate();
	void MouseUpdate();
	void Update();
	void SettingsInput();
	void MenuInput();
	void Input();
	void CreateButton(SoundBuffer&, Texture&, Font&, std::string, int, int, int, int, int, list<Button*>&);
	void TextInit();
	void AudioInit();
	void BackgroundInit();
	void ButtonInit();
};