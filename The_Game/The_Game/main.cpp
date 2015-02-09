#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include "player.h"
#include "Armor.h"

int main()
{
	enum Direction { Down, Left, Right, Up };

	sf::Vector2u source1(1, Down);
	sf::Vector2u source2(1, Down);

	sf::Clock hodiny;
	sf::Clock moveClock;

	player hrac;

	armor *brneni = 0;

	int fps = 0;
	sf::Clock fpsClock;

	sf::RenderWindow Window;
	Window.create(sf::VideoMode(400, 400), "Best Game");

	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Escape)
					Window.close();
				else if (Event.key.code == sf::Keyboard::LAlt)
				{
					brneni = new armor;
				}
				else if (brneni && Event.key.code == sf::Keyboard::LControl)
				{
					std::cout << brneni->time_left().asSeconds() << std::endl;
					std::cout << brneni->armor_left() << std::endl;
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


		// Konec brneni?

		if (brneni && brneni->time_left().asSeconds() > 10) 
		{
			brneni->~armor();
			brneni = 0;
		}
		else if (brneni) // Else draw armor
		{
			brneni->armorImage.setPosition(hrac.playerImage.getPosition().x - 10, hrac.playerImage.getPosition().y - 10);

			Window.draw(brneni->armorImage);
		}

		if (moveClock.getElapsedTime().asMilliseconds() > 10)
		{
			source1.y = hrac.move();

			moveClock.restart();
		}

		if (hodiny.getElapsedTime().asMilliseconds() > (400 / hrac.speed) )
		{
			source1.x++;
			source2.x++;
			hodiny.restart();
		}
		
		if (source1.x * 32 >= hrac.pTexture.getSize().x)
			source1.x = 0;

		hrac.playerImage.setTextureRect(sf::IntRect(source1.x * 32, source1.y * 32, 32, 32));

		Window.draw(hrac.playerImage);
		Window.display();
		Window.clear();

		if (fpsClock.getElapsedTime().asSeconds() > 1)
		{
			system("cls");

			std::cout << "FPS = " << fps << std::endl;

			fpsClock.restart();

			fps = 0;
		}
		else fps++;
	}

	delete brneni;
}