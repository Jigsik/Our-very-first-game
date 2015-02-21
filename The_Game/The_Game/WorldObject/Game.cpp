#include "Game.h"

Game::Game()
{
	Window.create(sf::VideoMode(600, 400), "Hovnocuc"); // OK

	setUpFont();
	setUpSound();
}

Game::~Game()
{
	if (rune)
	{
		rune->~Rune();
		delete rune;
	}
}

void Game::setUpFont()
{
	if (!gameFont.loadFromFile("Fonts/Face Your Fears.ttf"))
		std::cout << "Cannot load game Font" << std::endl;
	else std::cout << "Success loading game Font" << std::endl;

	fpsText.setFont(gameFont);
	fpsText.setPosition(sf::Vector2f((float)Window.getSize().x - 80, 0));
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

	Window.draw(fpsText);
}

void Game::handlingRunes()
{
	if (!rune && runeClock.getElapsedTime().asSeconds() > 5)
	{
		rune = new Rune;
	}

	if (rune)
	{
		if (rune->runeClock.getElapsedTime().asSeconds() > 10)
		{
			rune->~Rune();
			rune = 0;
			runeClock.restart();
		}
		else
		{
			Window.draw(rune->image);
		}
	}
}

void Game::play()
{
	Window.setFramerateLimit(0); // OK

	while (Window.isOpen()) // OK
	{
		Window.clear(sf::Color(30, 40, 200));

		while (Window.pollEvent(gameEvent))
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

		handlingRunes();

		countFPS();

		player.changeState();

		Window.draw(player.image);

		Window.display();
	}

	gameMusic.stop();

	Window.close(); // OK
}