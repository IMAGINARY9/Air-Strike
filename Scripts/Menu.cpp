#include "Menu.h"

#define PLAY "Play"
#define SETTINGS "Settings"
#define EXIT "Exit"
#define HARD "Hard"
#define MEDIUM "Medium"
#define EASY "Easy"
#define BACK "Back"
#define UP "+"
#define DOWN "-"

void Menu::run()
{
	Render();
	Update();
	Input();
}

void Menu::Render()
{
	if (isSettings)
	{
		window.draw(background2);
		window.draw(volumeText);
		for (auto const& el : settingsButtons)  el->draw(window);
	}
	else
	{
		window.draw(background);
		for (auto const& el : menuButtons)  el->draw(window);
	}
	window.display();
}

void Menu::MusicUpdate()
{
	if (music.getStatus() == SoundSource::Status::Stopped)
	{
		music.play();
	}
}
void Menu::MouseUpdate()
{
	mousePos = Mouse::getPosition(window);
	if (isSettings) {
		for (auto const& el : settingsButtons)  el->update(mousePos);
	}
	else {
		for (auto const& el : menuButtons)  el->update(mousePos);
	}
}

void Menu::Update()
{	
	MusicUpdate();
	MouseUpdate();
}

void Menu::SettingsInput()
{
	for (auto const& el : settingsButtons)
	{
		if (el->GetSprite().getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			if (el->GetText() == HARD)
			{
				Timer::SetTimeScale(1.5f);
				el->Click();
			}
			if (el->GetText() == MEDIUM)
			{
				Timer::SetTimeScale(1);
				el->Click();
			}
			if (el->GetText() == EASY)
			{
				Timer::SetTimeScale(0.75);
				el->Click();
			}
			if (el->GetText() == BACK)
			{
				isSettings = false;
				Settings::SetDifficult(Timer::GetTimeScale());
				el->Click();
			}

			if (el->GetText() == UP)
			{
				el->Click();
				if (Settings::GetVolume() <= 90)
				{
					Settings::SetVolume(Settings::GetVolume() + 10);
				}
				music.setVolume(Settings::GetVolume());
			}
			if (el->GetText() == DOWN)
			{
				el->Click();
				if (Settings::GetVolume() > 10)
				{
					Settings::SetVolume(Settings::GetVolume() - 10);
				}
				music.setVolume(Settings::GetVolume());
			}
			if (el->GetText() == "")
			{
				el->Click();
				Settings::SetVolume(0);
				music.setVolume(Settings::GetVolume());
			}

			volumeText.setString(to_string(Settings::GetVolume()));
		}
	}
}

void Menu::MenuInput()
{
	for (auto const& el : menuButtons)
	{
		if (el->GetSprite().getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			if (el->GetText() == PLAY)
			{
				Settings::SetIsGameRunning(true);
				music.stop();
				el->Click();
			}
			if (el->GetText() == SETTINGS)
			{
				isSettings = true;
				el->Click();
			}
			if (el->GetText() == EXIT)
			{
				window.close();
				el->Click();
			}
		}
	}
}

void Menu::Input()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.key.code == Mouse::Left)
			{
				if (isSettings)
				{
					SettingsInput();
				}
				else
				{
					MenuInput();
				}
			}
		}
	}
}

void Menu::CreateButton(SoundBuffer& sb, Texture& t, Font& f, std::string str, int x, int y, int w, int h, int offset, list<Button*>& list)
{
	Button* b = new Button();
	b->settings(sb, t, f, str, x, y, w, h, offset);
	list.push_back(b);
}

void Menu::TextInit()
{
	font.loadFromFile("assets/Font.ttf");
	volumeText.setFont(font);
	volumeText.setPosition(W * 0.73f, H * 0.75f);
	volumeText.setOutlineThickness(5);
	volumeText.setOutlineColor(Color::Black);
	volumeText.setCharacterSize(100);
	volumeText.setString(to_string(Settings::GetVolume()));
}
void Menu::AudioInit()
{
	ClkBf.loadFromFile("assets/Audio/Click.ogg");
	music.openFromFile("assets/Audio/Menu.ogg");
	music.setLoop(true);
	music.setVolume(Settings::GetVolume());
}
void Menu::BackgroundInit()
{
	bg.loadFromFile("assets/Menu.png");
	bg2.loadFromFile("assets/MenuBlur.png");
	background.setTexture(bg);
	background2.setTexture(bg2);
}
void Menu::ButtonInit()
{
	btn.loadFromFile("assets/Button.png");
	sbtn.loadFromFile("assets/SmallButton.png");
	mbtn.loadFromFile("assets/Mute.png");
	int tempW = 545;
	int tempH = 135;
	CreateButton(ClkBf, btn, font, PLAY, 1200, 100, tempW, tempH, 0, menuButtons);
	CreateButton(ClkBf, btn, font, SETTINGS, 1200, 300, tempW, tempH, -100, menuButtons);
	CreateButton(ClkBf, btn, font, EXIT, 100, 850, tempW, tempH, 0, menuButtons);

	int tempX = W * 0.35f;
	CreateButton(ClkBf, btn, font, HARD, tempX, H * 0.25f, tempW, tempH, 0, settingsButtons);
	CreateButton(ClkBf, btn, font, MEDIUM, tempX, H * 0.4f, tempW, tempH, -50, settingsButtons);
	CreateButton(ClkBf, btn, font, EASY, tempX, H * 0.55f, tempW, tempH, 0, settingsButtons);
	CreateButton(ClkBf, btn, font, BACK, tempX, H * 0.75f, tempW, tempH, 0, settingsButtons);
	int tempX2 = W * 0.72f;
	CreateButton(ClkBf, sbtn, font, UP, tempX2, H * 0.25f, tempH, tempH, -tempH+7, settingsButtons);
	CreateButton(ClkBf, sbtn, font, DOWN, tempX2, H * 0.4f, tempH, tempH, -tempH+3, settingsButtons);
	CreateButton(ClkBf, mbtn, font, "", tempX2, H * 0.55f, tempH, tempH, 0, settingsButtons);
}

Menu::Menu(RenderWindow& w) : window(w)
{
	TextInit();
	AudioInit();
	BackgroundInit();
	isSettings = false;
	ButtonInit();
}