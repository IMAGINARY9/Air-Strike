#include "Game.h"

void Game::run()
{
    Render();
    Update();
    Input();
}

void Game::Render()
{
    window.draw(background);

    for (const auto& el : entities) el->draw(window);

    window.draw(ind);
    window.draw(rectangle, 4, Quads);
    window.draw(scoreText);
    window.draw(lifeText);
    if (playerDied)
    {
        window.draw(titlesText);
        window.draw(titlesSmallText);
    }

    window.display();
}

void Game::RespawnEnemy()
{
    Enemy* e = new Enemy();
    e->settings(rand() % W, rand() % H, rand() % 360, 32);
    e->p = p;
    entities.push_back(e);
}

void Game::CreateExplosion(Entity* obj)
{
    Explosion* e = new Explosion();
    e->settings(obj->GetX(), obj->GetY(), obj->GetAngle(), 32);
    entities.push_back(e);
    explosionSound.play();
}

void Game::ColsCheckUpdate()
{
    for (const auto& a : entities)
    {
        if (a->GetName() == ENEMY && ((Enemy*)a)->GetFire())
        {
            Enemy* tempEnemy = (Enemy*)a;
            if (tempEnemy->GetClock().getElapsedTime().asSeconds() > 0.5f)
            {
                tempEnemy->RestartClock();
                shootEnemySound.play();
                Bullet* b = new Bullet();
                b->settings(tempEnemy->GetX(), tempEnemy->GetY(), tempEnemy->GetAngle(), 32);
                b->SetName(ENEMYBULLET);
                entities.push_back(b);
            }
        }
        for (const auto& b : entities)
        {

            if ((a->GetName() == PLAYER || a->GetName() == ENEMY) && b->GetName() == CLOUD)
            {
                if (checkCollide(a, b))
                {
                    a->broke(false);
                    break;
                }
                else
                    a->broke(true);
            }
            if (a->GetName() == PLAYER && (b->GetName() == ENEMY || b->GetName() == ENEMYBULLET))
            {
                if (checkCollide(a, b))
                {
                    CreateExplosion(a);
                    p->settings(rand() % W, rand() % H, rand() % 360, 32, 0);
                    b->SetLife(0);
                    a->SetLife(a->GetLife() - 1);
                    if (b->GetName() == ENEMY)
                    {
                        CreateExplosion(b);
                        RespawnEnemy();
                    }
                }
            }
            if (a->GetName() == MYBULLET && b->GetName() == ENEMY)
            {
                if (checkCollide(a, b))
                {
                    score++;
                    a->SetLife(0);
                    CreateExplosion(b);
                    b->SetLife(0);
                    RespawnEnemy();
                }
            }
        }
    }
}

Music* Game::getRandomMusic()
{
    return playlist[rand() % playlist.size()];
}

void Game::SetVolume()
{
    int value = Settings::GetVolume();
    shootSound.setVolume(value);
    shootEnemySound.setVolume(value);
    explosionSound.setVolume(value);
    reloadSound.setVolume(value);
    for(auto &el : playlist)
    {
        el->setVolume(value);
    }
    currentMusic->setVolume(value);
}

void Game::PlayerUpdate()
{
    if (p->GetLife() <= 5)
    {
        playerDied = true;
        p->SetLife(5);
        Timer::SetTimeScale(0);
        return;
    }
}
void Game::MusicUpdate()
{
    
    if (currentMusic->getStatus() == SoundSource::Status::Stopped)
    {
        currentMusic = getRandomMusic();
        currentMusic->play();
    }
    if (currentMusic->getStatus() == SoundSource::Status::Paused)
    {
        currentMusic->play();
    }
    SetVolume();
}
void Game::IndicatorUpdate()
{
    rectangle[0].position.y = 300 - p->GetReload() / 3 * 200;
    rectangle[1].position.y = 300 - p->GetReload() / 3 * 200;

    rectangle[0].color.r = p->GetReload() / 3 * 254;
    rectangle[0].color.g = 256 - p->GetReload() / 3 * 255;

    rectangle[1].color.r = p->GetReload() / 3 * 254;
    rectangle[1].color.g = 256 - p->GetReload() / 3 * 255;
}
void Game::TextUpdate()
{
    scoreText.setString("Kills: " + to_string(score));
    lifeText.setString("Lifes: " + to_string(p->GetLife() - 5));
}
void Game::EntitiesUpdate()
{
    for (auto i = entities.begin(); i != entities.end();)
    {
        Entity* e = *i;

        e->update();

        if (e->GetLife() <= 0) { i = entities.erase(i); delete e; }
        else i++;
    }
}

void Game::Update()
{
	PlayerUpdate();
    MusicUpdate();
	if (!playerDied) {
		ColsCheckUpdate();
		IndicatorUpdate();
		TextUpdate();
		EntitiesUpdate();
	}
}

void Game::Restart()
{
    playerDied = false;
    score = 0;
    p->SetLife(10);
    p->SetReload(0);
    Timer::SetTimeScale(Settings::GetDifficult());
}

void Game::PlayerShoot()
{
    if (Keyboard::isKeyPressed(Keyboard::Space) && p->GetThrust())
    {
        if (clock.getElapsedTime().asSeconds() > 0.3f && p->GetReload() <= 3)
        {
            clock.restart();
            Bullet* b = new Bullet();
            b->settings(p->GetX(), p->GetY(), p->GetAngle(), 32);
            entities.push_back(b);
            shootSound.play();
        }
        if (p->GetReload() <= 3) {
            p->SetReload(p->GetReload() + Timer::deltaTime());
        }
        if (clock.getElapsedTime().asSeconds() < 0.3f && p->GetReload() >= 3){
            reloadSound.play();
        }
    }
    else if (p->GetReload() > 0)
    {
        p->SetReload(p->GetReload() - Timer::deltaTime());
    }
}
void Game::PlayerMove()
{
    if (p->GetThrust()) {
        p->SetTextureX(64);
        p->SetTextureY(64);
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            p->SetAngle(p->GetAngle() + 0.25);
            p->SetTextureX(128);
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            p->SetAngle(p->GetAngle() - 0.25);
            p->SetTextureX(0);
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            p->SetBoost(0.25);
            p->SetTextureY(128);
        }
        else if (Keyboard::isKeyPressed(Keyboard::S)) p->SetBoost(-0.25);
        else
            p->SetBoost(0);
    }
    else
        p->SetTextureY(0);
}
void Game::Input()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
        if (event.type == Event::KeyPressed)
        { 
            if (event.key.code == Keyboard::Escape)
            {
                Settings::SetIsGameRunning(false);
                currentMusic->pause();
            }
            if (event.key.code == Keyboard::R)
            {
                Restart();
            }
        }
    }
    if (playerDied)
    {
        return;
    }
    PlayerShoot();
    PlayerMove();
}

void Game::TextCreate(Text& text, Font& font, int x, int y, int outline, int size, Color cl)
{
    text.setFont(font);
    text.setPosition(x, y);
    text.setOutlineThickness(outline);
    text.setCharacterSize(size);
    text.setOutlineColor(cl);
}

void Game::AudioInit()
{
    shootBuffer.loadFromFile("assets/Audio/Shoot.ogg");
    shootEnemyBuffer.loadFromFile("assets/Audio/ShootEnemy.ogg");
    explosionBuffer.loadFromFile("assets/Audio/Explosion.ogg");
    reloadBuffer.loadFromFile("assets/Audio/Reload.ogg");
    shootSound.setBuffer(shootBuffer);
    shootEnemySound.setBuffer(shootEnemyBuffer);
    explosionSound.setBuffer(explosionBuffer);
    reloadSound.setBuffer(reloadBuffer);
    for (int i = 0; i < 3; i++)
    {
        Music* m = new Music();
        playlist.push_back(m);
    }
    playlist[0]->openFromFile("assets/Audio/Stereoalex_-_Go_Ahead.ogg");
    playlist[1]->openFromFile("assets/Audio/Dan_Ryan_-_Mirror_Mirror.ogg");
    playlist[2]->openFromFile("assets/Audio/Infraction_-_Fire_Inside_Me.ogg");
    currentMusic = getRandomMusic();
    SetVolume();
}
void Game::BackgroundInit()
{
    bg.loadFromFile("assets/background.png");
    background.setTexture(bg);
    background.setScale(0.5f, 0.5f);
}
void Game::TextInit()
{
    font.loadFromFile("assets/Font.ttf");
    TextCreate(scoreText, font, 50, 35, 5, 30, Color::Black);
    TextCreate(lifeText, font, 200, 35, 5, 30, Color::Black);
    TextCreate(titlesText, font, W * 0.20, H * 0.35, 10, 300, Color::Black);
    TextCreate(titlesSmallText, font, W * 0.35, H * 0.65, 5, 70, Color::Black);

    titlesText.setString("You died");
    titlesSmallText.setString("Press R to restart");
}
void Game::PlayerInit()
{
    this->p = new Player();
    p->settings(W * 0.45, H, 0, 32, 0);
    entities.push_back(p);
}
void Game::EnemyInit()
{
    for (int i = 0; i < 5; i++)
    {
        RespawnEnemy();
    }
}
void Game::CloudInit()
{
    for (int i = 0; i < 5; i++)
    {
        Cloud* c = new Cloud();
        c->settings(rand() % W, rand() % H, rand() % 360, 128);
        entities.push_back(c);
    }
}
void Game::ReloadIndicatorInit()
{
    in.loadFromFile("assets/Indicator.png");
    ind.setTexture(in);
    this->rectangle[0] = Vertex(Vector2f(50, 100), Color::Color(189, 59, 86, 255));
    this->rectangle[1] = Vertex(Vector2f(100, 100), Color::Color(189, 59, 86, 255));
    this->rectangle[2] = Vertex(Vector2f(100, 300), Color::Color(98, 117, 67, 255));
    this->rectangle[3] = Vertex(Vector2f(50, 300), Color::Color(98, 117, 67, 255));
    ind.setPosition(Vector2f(35, 85));
}

Game::Game(RenderWindow& w) : window(w)
{
    score = 0;
    playerDied = false;

    AudioInit();
    BackgroundInit();
    TextInit();
    PlayerInit();
    EnemyInit();
    CloudInit();
    ReloadIndicatorInit();
}

bool Game::checkCollide(Entity* a, Entity* b)
{
    return (b->GetX() - a->GetX()) * (b->GetX() - a->GetX()) +
        (b->GetY() - a->GetY()) * (b->GetY() - a->GetY()) <
        (a->GetR() + b->GetR()) * (a->GetR() + b->GetR());
}
