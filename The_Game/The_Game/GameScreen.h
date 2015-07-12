#include "cScreen.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include "WorldObject/Player1.h"
//#include "Rune.h"
#include "WorldObject/Bullet.h"
#include "WorldObject/Map.h"
#include "RuneFactory.h"
#include "Settings.h"

class GameScreen : public cScreen
{
public:
	GameScreen(sf::RenderWindow &App, Settings &settings);
	~GameScreen(void);
	virtual int Run(sf::RenderWindow &App);
	void play();

private:
	void setUpFont(); // OK
	void setUpSound();
	void countFPS();
	void handlingRunes();
	void collisions();
	void handlingBuffs();
	void handlingMissiles();
	void hanglingCharacters();
	void handlingViews();
	void draw();

	bool isPause = false;

protected:
	enum Types { armorRune, speedRune };

	// Texts
	sf::Font gameFont; // OK
	sf::String fpsString; // OK
	sf::Text fpsText; // OK
	sf::Event gameEvent; // OK
	int fps = 0; // OK

	// Window
	sf::RenderWindow *Window = 0; // OK
	sf::Vector2u screenDimensions = sf::Vector2u(800, 0);
	sf::Vector2f position;

	// Clocks
	sf::Clock fpsClock, enemiesClock, rocketsClock, armorClock,
		runeClock, bulletsClock, resetClock; // OK

	// Sound
	sf::Music gameMusic;

	// Objects
	Player player;
	//Rune *rune = 0;

	// Runes
	std::vector<Rune*> runes;
	std::vector<Rune*>::iterator runesIt;

	// Missiles
	std::vector<Bullet*> bullets;
	std::vector<Bullet*>::iterator bulletsIt;

	// Views
	sf::View player1_view;
	sf::View player2_view;
	sf::View barView1;
	sf::View barView2;

	// Map
	Map mapa;

	// Settings
	Settings settings;
};

GameScreen::GameScreen(sf::RenderWindow &App, Settings &settings)
{
	Window = &App;
	this->settings = settings;

	screenDimensions.y = (screenDimensions.x * Window->getSize().y) / Window->getSize().x;

	setUpFont();
	setUpSound();

	if (!mapa.load(settings.getMapLocation()))
		std::cout << "Failed to load map at location : " << settings.getMapLocation() << std::endl;
}

GameScreen::~GameScreen(void)
{
	// Delete rune if exists
	//if(rune)
	//delete rune;

	for (runesIt = runes.begin(); runesIt != runes.end();)
	{
		delete *runesIt;
		runesIt = runes.erase(runesIt);
	}

	// Delete all existing bullets
	for (bulletsIt = bullets.begin(); bulletsIt != bullets.end();)
	{
		delete *bulletsIt;
		bulletsIt = bullets.erase(bulletsIt);
	}
}

void GameScreen::setUpFont()
{
	if (!gameFont.loadFromFile(settings.getFontLocation()))
		std::cout << "Cannot load game Font" << std::endl;
	else std::cout << "Success loading game Font" << std::endl;

	fpsText.setFont(gameFont);
	fpsText.setCharacterSize((Window->getSize().x / screenDimensions.x) * 20);
	fpsText.setPosition(sf::Vector2f((float)Window->getSize().x - (Window->getSize().x / screenDimensions.x) * 50, 0));
}

void GameScreen::setUpSound()
{
	if (!gameMusic.openFromFile(settings.getMusicLocation()))
		std::cout << "Unable to load game Music." << std::endl;
	else std::cout << "Success loading game Music" << std::endl;

	gameMusic.setLoop(true);
	//gameMusic.play();
	gameMusic.setVolume(settings.getMusicVolume());
}

void GameScreen::countFPS()
{
	if (fpsClock.getElapsedTime().asMilliseconds() > 500)
	{
		fpsString = std::to_string(fps * 2);
		fpsClock.restart();
		fps = 0;
	}
	else fps++;

	fpsText.setString(fpsString);

	Window->setView(Window->getDefaultView());

	Window->draw(fpsText);

	//fpsText.setScale(Window->getSize().x / screenDimensions.x, Window->getSize().y / screenDimensions.y);
}

void GameScreen::handlingRunes()
{
	if (runeClock.getElapsedTime().asMilliseconds() > settings.getRuneRespawnTime())
	{
		runes.push_back(RuneFactory::createRune(rand() % settings.getRunesCount(), mapa.getSize()));
		runeClock.restart();
	}

	for (runesIt = runes.begin(); runesIt != runes.end();)
	{
		if ((*runesIt)->runeClock.getElapsedTime().asSeconds() > (*runesIt)->getDuration())
		{
			delete *runesIt;
			runesIt = runes.erase(runesIt);
		}
		else runesIt++;
	}
}

void GameScreen::handlingBuffs()
{
	player.drawBuffs(Window, player1_view, player2_view, barView1, barView2);
}

void GameScreen::handlingMissiles()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && bulletsClock.getElapsedTime().asMilliseconds() > 350)
	{
		bullets.push_back(new Bullet(player.getPosition(), player.getDirection(), player.getSize()));
		bulletsClock.restart();
	}

	for (bulletsIt = bullets.begin(); bulletsIt != bullets.end(); bulletsIt++)
	{
		(*bulletsIt)->changeState(Window);
	}
}

void GameScreen::hanglingCharacters()
{
	Window->setView(barView1);
	player.changeState(Window);

	Window->setView(barView2);
	player.changeState(Window);
}

void GameScreen::collisions()
{
	// Player and the rune

	float playerLeft = player.getPosition().x;
	float playerRight = player.getPosition().x + player.getSize().x;
	float playerTop = player.getPosition().y;
	float playerBottom = player.getPosition().y + player.getSize().y;

	for (runesIt = runes.begin(); runesIt != runes.end(); runesIt++)
	{
		float runeLeft = (*runesIt)->getPosition().x;
		float runeRight = (*runesIt)->getPosition().x + (*runesIt)->getSize().x;
		float runeTop = (*runesIt)->getPosition().y;
		float runeBottom = (*runesIt)->getPosition().y + (*runesIt)->getSize().y;

		if (playerLeft <= runeRight &&
			playerRight >= runeLeft &&
			playerTop <= runeBottom &&
			playerBottom >= runeTop)
		{
			// Get the rune type
			int runeType = (*runesIt)->getType();

			// Which rune have you taken?
			if (runeType == armorRune)
			{
				player.activateArmor();
			}
			else if (runeType == speedRune)
			{
				player.activateSpeed();
			}

			delete *runesIt;
			runesIt = runes.erase(runesIt);

			// If player get the rune, there is a big change that he is not getting any other
			// rune. So we can break here and control it later.
			break;
		}
	}

	/*if (rune)
	{
	float runeLeft = rune->getPosition().x;
	float runeRight = rune->getPosition().x + rune->getSize().x;
	float runeTop = rune->getPosition().y;
	float runeBottom = rune->getPosition().y + rune->getSize().y;

	if (playerLeft <= runeRight &&
	playerRight >= runeLeft &&
	playerTop <= runeBottom &&
	playerBottom >= runeTop)
	{
	// Get the rune type
	int runeType = rune->getType();

	// Which rune have you taken?
	if (runeType == armorRune)
	{
	player.activateArmor();
	}
	else if (runeType == speedRune)
	{
	player.activateSpeed();
	}

	// Clean memory, set rune to zero and restart the clock
	delete rune;
	rune = 0;
	runeClock.restart();
	}
	}*/
}

void GameScreen::handlingViews()
{
	position.x = player.getPosition().x + player.getSize().x - (screenDimensions.x * 0.5f * 0.495f);
	position.y = player.getPosition().y + player.getSize().y - (screenDimensions.y * 0.5f * 0.95f);

	if (position.x <= 0)
		position.x = 0;
	else if (position.x > mapa.getSize().x - (screenDimensions.x * 0.495f))
		position.x = mapa.getSize().x - (screenDimensions.x * 0.495f);

	if (position.y <= 0)
		position.y = 0;
	else if (position.y > mapa.getSize().y - screenDimensions.y * 0.95f)
		position.y = mapa.getSize().y - screenDimensions.y * 0.95f;

	//player1_view.rotate(0.01f);

	/* VELIKA POZNAMKA

	player1_view.reset(sf::FloatRect(position.x, position.y, (float)(screenDimensions.x / 2), (float)screenDimensions.y));

	Tento kod je spatne, protoze to view nema rozsah screenDimension.x / 2 a screenDimension.y...

	Takhle to je spravne:

	player2_view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x * 0.495f, screenDimensions.y * 0.95f));

	*/

	player1_view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x * 0.495f, screenDimensions.y * 0.95f));
	player2_view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x * 0.495f, screenDimensions.y * 0.95f));

	player1_view.zoom(0.5f);

	//std::cout << player1_view.getCenter().x << " " << player1_view.getCenter().y << std::endl;

	// previous line is just copied and set to view 2 so we can see tha same screen;

	//player1_view.move(0.01, 0.01)
}

void GameScreen::draw()
{
	for (runesIt = runes.begin(); runesIt != runes.end(); runesIt++)
	{
		Window->setView(player1_view);
		Window->draw((*runesIt)->image);

		Window->setView(player2_view);
		Window->draw((*runesIt)->image);
	}

	/*if (rune)
	{
	Window->setView(player1_view);
	Window->draw(rune->image);

	Window->setView(player2_view);
	Window->draw(rune->image);
	}*/

	for (bulletsIt = bullets.begin(); bulletsIt != bullets.end(); bulletsIt++)
	{
		Window->setView(player1_view);
		Window->draw((*bulletsIt)->image);

		Window->setView(player2_view);
		Window->draw((*bulletsIt)->image);
	}

	Window->setView(player1_view);
	Window->draw(player.image);

	Window->setView(player2_view);
	Window->draw(player.image);
}

int GameScreen::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;

	player1_view.setViewport(sf::FloatRect(0, 0, 0.495f, 0.95f));
	player2_view.setViewport(sf::FloatRect(0.505f, 0, 0.495f, 0.95f));
	barView1.setViewport(sf::FloatRect(0, 0.95f, 0.5f, 0.05f));
	barView2.setViewport(sf::FloatRect(0.5f, 0.95f, 0.5f, 0.05f));

	barView1.reset(sf::FloatRect(0, 0, (float)App.getSize().x / 2, (float)App.getSize().y / 20));
	barView2.reset(sf::FloatRect(0, 0, (float)App.getSize().x / 2, (float)App.getSize().y / 20));

	while (Running)
	{
		//Clearing screen
		App.clear(sf::Color(0, 0, 0, 0));

		App.setView(player1_view);
		App.draw(mapa);

		App.setView(player2_view);
		App.draw(mapa);

		App.setView(player1_view);

		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Escape:
					Window->setView(Window->getDefaultView());
					return 0;
					break;
				default:
					break;
				}
			}
		}

		//Drawing
		collisions();
		handlingRunes();
		handlingBuffs();
		App.setView(player1_view);
		handlingMissiles();
		hanglingCharacters();

		draw();

		countFPS();

		App.setView(player1_view);

		handlingViews();

		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}