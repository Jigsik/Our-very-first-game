#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "player.h"
#include "enemy.h"
#include "rocket_missiles.h"

void pause(sf::RenderWindow* Window)
{
	// Asi netreba, ale jeste to tu pro jistotu necham, kdyby se zjistilo, ze to potreba je.
	//Window->setKeyRepeatEnabled(false);

	sf::Listener::setGlobalVolume(0);

	sf::RectangleShape obraz(sf::Vector2f((float)Window->getSize().x, (float)Window->getSize().y));
	obraz.setFillColor(sf::Color(0,0,0,150));

	// The name of the Font
	sf::Font pauseFont;

	// Loading Font from file
	if (!pauseFont.loadFromFile("Fonts/Face Your Fears.ttf"))
		std::cout << "Cannot load font for Pause" << std::endl;

	// What will appear on the menu window
	sf::String paused = "PAUSED";

	// Properties of menu texts
	sf::Text pauza;
	pauza.setString(paused);
	pauza.setFont(pauseFont);

	// Positions of menu texts
	pauza.setPosition(sf::Vector2f((float)Window->getSize().x / 5, (float)Window->getSize().y / 5));

	Window->draw(obraz);
	Window->draw(pauza);
	Window->display();

	sf::Event Event;

	while (Window->waitEvent(Event))
	{
		switch (Event.type)
		{
		case sf::Event::KeyReleased:
			if (Event.key.code == sf::Keyboard::P)
			{
				sf::Listener::setGlobalVolume(100);

				return;
			}
		}
	}
}

void game(sf::RenderWindow* Window)
{
	bool isPause = false;

	Window->setFramerateLimit(500);

	// FPS

	// The name of the Font
	sf::Font fpsFont;

	// Loading Font from file
	if (!fpsFont.loadFromFile("Fonts/Face Your Fears.ttf"))
		std::cout << "Cannot load font for Pause" << std::endl;

	// What will appear on the menu window
	sf::String fpsString;

	int fps = 0;
	sf::Clock fpsClock;

	// Properties of menu texts
	sf::Text fpsText;
	fpsText.setFont(fpsFont);
	

	// Positions of FPS text
	fpsText.setPosition(sf::Vector2f((float)Window->getSize().x - 80, 0));

	// Sound

	sf::Music music;

	if (!music.openFromFile("Sounds/music.wav"))
	{
		std::cout << "Unable to load music." << std::endl;
	}

	music.setLoop(true);
	music.play();
	music.setVolume(50);

	player hrac;

	std::vector<rocket_missile*> rockets;
	std::vector<enemy*> enemies;
	sf::Clock enemiesClock, rocketsClock, brneniClock;

	while (Window->isOpen())
	{
		sf::Event Event;
		while (Window->pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Escape)
				{
					return;
				}
				else if (Event.key.code == sf::Keyboard::LAlt)
				{
					hrac.activateArmor();
				}
				break;
			case sf::Event::KeyReleased:
				if (Event.key.code == sf::Keyboard::P)
				{
					isPause = true;
				}
				break;
			case sf::Event::JoystickConnected:
				std::cout << "Joystick " << Event.joystickConnect.joystickId + 1 << " is connected!" << std::endl;
				break;
			case sf::Event::JoystickDisconnected:
				std::cout << "Joystick " << Event.joystickConnect.joystickId + 1 << " is disconnected!" << std::endl;
				break;
			case sf::Event::JoystickButtonPressed:
				std::cout << "Button: " << Event.joystickButton.button << std::endl;
				break;
			case sf::Event::JoystickMoved:
				if (Event.joystickMove.axis == sf::Joystick::X)
				{
					std::cout << "Position: " << Event.joystickMove.position << std::endl;
				}
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && rocketsClock.getElapsedTime().asMilliseconds() > 350)
		{
			rockets.push_back(new rocket_missile(hrac.getPosition(), hrac.getDirection(), hrac.getCharacterSize()));
			rocketsClock.restart();
		}

		if (enemiesClock.getElapsedTime().asSeconds() > 1)
		{
			enemies.push_back(new enemy);
			enemiesClock.restart();
		}

		std::vector<rocket_missile*>::iterator Veciter;
		for (Veciter = rockets.begin(); Veciter != rockets.end(); Veciter++)
		{
			(*Veciter)->draw(Window);
		}
		
		if (fpsClock.getElapsedTime().asSeconds() > 1)
		{
			fpsString = std::to_string(fps);

			fpsClock.restart();

			fps = 0;
		}
		else fps++;

		fpsText.setString(fpsString);

		Window->draw(fpsText);

		hrac.draw(Window);

		std::vector<enemy*>::iterator EneIter;
		for (EneIter = enemies.begin(); EneIter != enemies.end();)
		{
			(*EneIter)->draw(Window, hrac.getPosition());

			float enemyRight = (*EneIter)->getPosition().x + (float)(*EneIter)->getSize().x;
			float enemyLeft = (*EneIter)->getPosition().x;
			float enemyBottom = (*EneIter)->getPosition().y + (float)(*EneIter)->getSize().y;
			float enemyTop = (*EneIter)->getPosition().y;
			float playerRight = hrac.getPosition().x + (float)hrac.getCharacterSize().x;
			float playerLeft = hrac.getPosition().x;
			float playerTop = hrac.getPosition().y;
			float playerBottom = hrac.getPosition().y + hrac.getCharacterSize().y;

			if (playerLeft <= enemyRight &&
				playerRight >= enemyLeft &&
				playerTop <= enemyBottom &&
				playerBottom >= enemyTop)
			{
				EneIter = enemies.erase(EneIter);

				hrac.recieveDamage(20);
			}
			else ++EneIter;
		}

		// BEGIN COLLISION

		std::vector<rocket_missile*>::iterator rocketIter5;
		std::vector<enemy*>::iterator enemyIter5;

		for (rocketIter5 = rockets.begin(); rocketIter5 != rockets.end();)
		{
			bool collision = false;

			for (enemyIter5 = enemies.begin(); enemyIter5 != enemies.end(); enemyIter5++)
			{
				//float rocketLeft = (*rocketIter5)->getPosition().x;
				//float rocketRight = (*rocketIter5)->getPosition().x + (float)(*rocketIter5)->getSize().x;
				//float rocketTop = (*rocketIter5)->getPosition().y;
				//float rocketBottom = (*rocketIter5)->getPosition().y + (float)(*rocketIter5)->getSize().y;
				float enemyRight = (*enemyIter5)->getPosition().x + (float)(*enemyIter5)->getSize().x;
				float enemyLeft = (*enemyIter5)->getPosition().x;
				float enemyBottom = (*enemyIter5)->getPosition().y + (float)(*enemyIter5)->getSize().y;
				float enemyTop = (*enemyIter5)->getPosition().y;

				//float rotation = (*rocketIter5)->getRotation();

				// jeste nejake ladeni. Opravdu tezko rict, jestli by nebylo lepsi delat vic animaci.

				/*if (rotation == 180 || rotation == 135)
				{
					rocketLeft = (*rocketIter5)->getPosition().x - (float)(*rocketIter5)->getSize().x;
					rocketRight = (*rocketIter5)->getPosition().x;
				}
				else if (rotation == 90 || rotation == 225)
				{
					rocketLeft = (*rocketIter5)->getPosition().x - (float)(*rocketIter5)->getSize().y;
					rocketRight = (*rocketIter5)->getPosition().x;
				}*/

				if ((*rocketIter5)->getPosition().x >= enemyLeft &&
					(*rocketIter5)->getPosition().x <= enemyRight &&
					(*rocketIter5)->getPosition().y >= enemyTop &&
					(*rocketIter5)->getPosition().y <= enemyBottom)
				{
					std::cout << "HIT" << std::endl;

					rocketIter5 = rockets.erase(rocketIter5);
					enemyIter5 = enemies.erase(enemyIter5);

					collision = true;

					break;
				}

				/*if (rocketLeft <= enemyRight && rocketRight >= enemyLeft &&
					  rocketTop <= enemyBottom && rocketBottom >= enemyTop)
				{
					std::cout << "HIT" << std::endl;

					rocketIter5 = rockets.erase(rocketIter5);
					enemyIter5 = enemies.erase(enemyIter5);

					collision = true;

					break;
				}*/
			}

			if (!collision)
				++rocketIter5;
		}

		// END COLLISION

		Window->display();

		if (isPause)
		{
			pause(Window);

			isPause = false;
		}

		Window->clear(sf::Color(0, 120, 120));
	}

	std::vector<rocket_missile*>::iterator rocketIter;
	for (rocketIter = rockets.begin(); rocketIter != rockets.end(); rocketIter++)
	{
		(*rocketIter)->~rocket_missile();
		delete *rocketIter;
	}

	std::vector<enemy*>::iterator dEneIter;
	for (dEneIter = enemies.begin(); dEneIter != enemies.end(); dEneIter++)
	{
		delete *dEneIter;
	}
}

void menu()
{
	// Z nejakeho duvodu hlasi AVAST virus pri tomto volani.
	// Z jeste podivnejsi duvodu uz to nehlasi
	sf::RenderWindow *Window = 0;
	Window = new sf::RenderWindow;

	// Create a window 600x400 with the title "Hovnocuc"
	Window->create(sf::VideoMode(600, 400), "Hovnocuc");

	// newGame = 0, konec = 1
	enum choice { newGame, konec };

	Window->setFramerateLimit(25);

	// newGame is active at the beginning
	int active = newGame;
	// Now we have 2 choices, so if we have x choices we would do choiceCount = x
	int choiceCount = 2;

	// The name of the Font
	sf::Font menuFont;
	
	// Loading Font from file
	if (!menuFont.loadFromFile("Fonts/Face Your Fears.ttf"))
		std::cout << "Cannot load font for Menu" << std::endl;

	// What will appear on the menu window
	sf::String new_game = "NEW GAME";
	sf::String exit = "EXIT";

	// Properties of menu texts
	sf::Text nova_hra;
	sf::Text konec_hry;
	nova_hra.setString(new_game);
	konec_hry.setString(exit);
	nova_hra.setFont(menuFont);
	konec_hry.setFont(menuFont);

	// Positions of menu texts
	nova_hra.setPosition(sf::Vector2f((float)Window->getSize().x / 5, (float)Window->getSize().y / 5));
	konec_hry.setPosition(sf::Vector2f((float)Window->getSize().x / 5, (float)Window->getSize().y / 3));

	// While the graphic window is open
	while (Window->isOpen())
	{
		sf::Event Event;

		// Take the Event which is on stack
		while (Window->pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Return)
				{
					if (active == newGame)
					{
						game(Window);
					}
					else if (active == konec)
						Window->close();
				}
				else if (Event.key.code == sf::Keyboard::Down)
				{
					if (active == 0) active = choiceCount - 1;
					else active--;
				}
				else if (Event.key.code == sf::Keyboard::Up)
				{
					if (active >= choiceCount - 1) active = 0;
					else active++;
				}
				break;
			}
		}

		if (active == 0)
		{
			nova_hra.setColor(sf::Color::Yellow);
			nova_hra.setStyle(sf::Text::Bold | sf::Text::Underlined);
			nova_hra.setCharacterSize(50);

			konec_hry.setColor(sf::Color::Blue);
			konec_hry.setCharacterSize(40);
		}
		else if (active == 1)
		{
			konec_hry.setColor(sf::Color::Yellow);
			konec_hry.setStyle(sf::Text::Bold | sf::Text::Underlined);
			konec_hry.setCharacterSize(50);

			nova_hra.setColor(sf::Color::Blue);
			nova_hra.setCharacterSize(40);
		}

		Window->draw(nova_hra);
		Window->draw(konec_hry);
		Window->display();
		Window->clear();
	}

	Window->~RenderWindow();

	delete Window;
}

int main()
{
	menu();
}