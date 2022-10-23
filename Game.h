#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>

#include "Settings.h"
#include "Timer.h"
#include "Player.h"
#include "Bullet.h"
#include "Cloud.h"
#include "Enemy.h"
#include "Explosion.h"

using namespace std;
#define PLAYER "player"
#define CLOUD "cloud"
#define ENEMY "enemy"
#define MYBULLET "bullet"
#define ENEMYBULLET "enemyBullet"

class Game
{
public:
	Game(RenderWindow&);
	void run();
private:
	void Render();
	void TextCreate(Text&, Font&, int, int, int, int, Color);
	void RespawnEnemy();
	void CreateExplosion(Entity*);

	void ColsCheckUpdate();
	void PlayerUpdate();
	void MusicUpdate();
	void IndicatorUpdate();
	void TextUpdate();
	void EntitiesUpdate();
	void Update();

	void Restart();
	void PlayerShoot();
	void PlayerMove();
	void Input();

	bool checkCollide(Entity* a, Entity* b);
	void SetVolume();
	Music* getRandomMusic();

	void AudioInit();
	void BackgroundInit();
	void TextInit();
	void PlayerInit();
	void EnemyInit();
	void CloudInit();
	void ReloadIndicatorInit();
	
	bool playerDied;
	Text scoreText;
	Text lifeText;
	Text titlesText;
	Text titlesSmallText;
	Font font;
	Clock clock;
	Music *currentMusic;
	vector<Music*> playlist;
	SoundBuffer shootBuffer;
	SoundBuffer shootEnemyBuffer;
	SoundBuffer explosionBuffer;
	SoundBuffer reloadBuffer;
	Sound shootSound;
	Sound shootEnemySound;
	Sound explosionSound;
	Sound reloadSound;
	RenderWindow& window;
	list<Entity*> entities;
	Texture bg, in;
	Sprite background, ind;
	Vertex rectangle[4];
	Player *p;
	int score;
};