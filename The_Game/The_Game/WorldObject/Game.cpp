#include "Game.h"

Game::Game()
{
	Window = new sf::RenderWindow;

	Window->create(sf::VideoMode(1000, 1000), "Hovnocuc"); // OK

	setUpFont();
	setUpSound();
	loadMap();
}

Game::~Game()
{
	// Delete rune if exists
	if(rune)
		delete rune;

	// Delete Window
	if (Window)
		delete Window;

	// Delete all existing bullets
	for (bulletsIt = bullets.begin(); bulletsIt != bullets.end();)
	{
		delete *bulletsIt;
		bulletsIt = bullets.erase(bulletsIt);
	}
}

void Game::setUpFont()
{
	if (!gameFont.loadFromFile("Fonts/STENCIL.ttf"))
		std::cout << "Cannot load game Font" << std::endl;
	else std::cout << "Success loading game Font" << std::endl;

	fpsText.setFont(gameFont);
	fpsText.setPosition(sf::Vector2f((float)Window->getSize().x - 50, 0));

	fpsText.setCharacterSize(20);
}

void Game::setUpSound()
{
	if (!gameMusic.openFromFile("Sounds/music.wav"))
		std::cout << "Unable to load game Music." << std::endl;
	else std::cout << "Success loading game Music" << std::endl;

	gameMusic.setLoop(true);
	gameMusic.play();
	gameMusic.setVolume(50);
}

void Game::loadMap()
{
	std::ifstream openfile("Maps/mapa.txt");

	if (openfile.is_open())
	{
		std::string tileLocation;
		std::getline(openfile, tileLocation);
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture);

		while (!openfile.eof())
		{
			std::string str, value;
			std::getline(openfile, str);
			std::stringstream stream(str);

			while (std::getline(stream, value, ','))
			{
				if (value.length() > 0)
					tempMap.push_back((atoi(value.c_str())) - 1);
			}

			map.push_back(tempMap);
			tempMap.clear();
		}
		tempMap.clear();
	}
	else std::cout << "Cannot open file" << std::endl;
}

void Game::countFPS()
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
}

void Game::handlingRunes()
{
	if (!rune && runeClock.getElapsedTime().asSeconds() > 3)
	{
		rune = new Rune;
	}

	if (rune)
	{
		if (rune->runeClock.getElapsedTime().asSeconds() > rune->getDuration())
		{
			delete rune;
			rune = 0;
			runeClock.restart();
		}
		else
		{
			Window->draw(rune->image);
		}
	}
}

void Game::handlingBuffs()
{
	player.drawBuffs(Window);
}

void Game::handlingMissiles()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && bulletsClock.getElapsedTime().asMilliseconds() > 350)
	{
		bullets.push_back(new Bullet(player.getPosition(), player.getDirection(), player.getSize()));
		bulletsClock.restart();
	}

	for (bulletsIt = bullets.begin(); bulletsIt != bullets.end(); bulletsIt++)
	{
		(*bulletsIt)->draw(Window);
	}
}

void Game::hanglingCharacters()
{
	player.draw(Window);

	Window->setView(view1);
}

void Game::collisions()
{
	// Player and the rune

	float playerLeft = player.getPosition().x;
	float playerRight = player.getPosition().x + player.getSize().x;
	float playerTop = player.getPosition().y;
	float playerBottom = player.getPosition().y + player.getSize().y;

	if (rune)
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
	}
}

void Game::play()
{
	view1.setCenter(300, 300);
	view1.setSize(600, 600);

	Window->setFramerateLimit(0); // OK

	while (Window->isOpen()) // OK
	{
		Window->clear(sf::Color(30, 40, 200));

		for (unsigned i = 0; i < map.size(); i++)
		{
			for (unsigned j = 0; j < map[i].size(); j++)
			{
				if (map[i][j] != -1)
				{
					tiles.setPosition((float)(j * 30), (float)(i * 30));
					tiles.setTextureRect(sf::IntRect((map[i][j] % 2) * 30, (map[i][j] / 2) * 30, 30, 30));
					Window->draw(tiles);
				}
			}
		}

		Window->setView(view1);

		while (Window->pollEvent(gameEvent))
		{
			switch (gameEvent.type)
			{
			case sf::Event::KeyPressed:
				if (gameEvent.key.code == sf::Keyboard::Escape)
				{
					return;
				}
				else if (gameEvent.key.code == sf::Keyboard::P)
				{
					isPause = true;
				}
				break;
			}
		}

		collisions();

		handlingRunes();

		handlingBuffs();

		Window->setView(view1);

		handlingMissiles();

		hanglingCharacters();

		countFPS();

		Window->setView(view1);

		Window->display();
	}

	gameMusic.stop();

	Window->close(); // OK
}