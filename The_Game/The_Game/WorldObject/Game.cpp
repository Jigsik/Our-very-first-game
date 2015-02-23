#include "Game.h"

Game::Game()
{
	Window = new sf::RenderWindow;

	Window->create(sf::VideoMode(600, 400), "Hovnocuc"); // OK

	setUpFont();
	setUpSound();
}

Game::~Game()
{
	if(rune)
		delete rune;

	if (Window)
		delete Window;
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
	Window->setFramerateLimit(0); // OK

	while (Window->isOpen()) // OK
	{
		Window->clear(sf::Color(30, 40, 200));

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

		countFPS();

		player.draw(Window);

		Window->display();
	}

	gameMusic.stop();

	Window->close(); // OK
}