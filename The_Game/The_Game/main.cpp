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

	player hrac;

	armor *brneni = 0;

	sf::RenderWindow Window;
	Window.create(sf::VideoMode(200, 200), "Best Game", sf::Style::Fullscreen);

	int nextPose;

	nextPose = 0;

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

		// Movement speed

		float movement_speed = (float) 0.013;

		// Increasing movement speed

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			movement_speed *= 2;
		}

		// First player movement

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			source1.y = Up;
			hrac.playerImage.move(0, -movement_speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			source1.y = Down;
			hrac.playerImage.move(0, movement_speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			source1.y = Left;
			hrac.playerImage.move(-movement_speed, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			source1.y = Right;
			hrac.playerImage.move(movement_speed, 0);
		}

		if ( nextPose == 2000 )
		{
			source1.x++;
			source2.x++;
			nextPose = 0;
		}
		else nextPose++;
		
		if (source1.x * 32 >= hrac.pTexture.getSize().x)
			source1.x = 0;

		hrac.playerImage.setTextureRect(sf::IntRect(source1.x * 32, source1.y * 32, 32, 32));

		Window.draw(hrac.playerImage);
		Window.display();
		Window.clear();
	}

	delete brneni;
}