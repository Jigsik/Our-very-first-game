#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
//#include "player.h"
#include "armor.h"

int main()
{
	enum Direction { Down, Left, Right, Up };

	sf::Vector2i source1(1, Down);
	sf::Vector2i source2(1, Down);

	//player hrac;

	armor *brneni;

	sf::RenderWindow Window;
	Window.create(sf::VideoMode(800, 600), "Best Game");

	/* Aby se neopakovali klavesy
	Window.setKeyRepeatEnabled(false);*/

	sf::Texture pTexture1;
	sf::Texture pTexture2;
	sf::Sprite playerImage1;
	sf::Sprite playerImage2;

	if (!pTexture1.loadFromFile("player_1.png"))
		std::cout << "Error could not load player image 1" << std::endl;

	if (!pTexture2.loadFromFile("player_2.png"))
		std::cout << "Error could not load player image 2" << std::endl;

	playerImage1.setTexture(pTexture1);
	playerImage2.setTexture(pTexture2);
	playerImage2.setPosition(100, 0);

	/*std::string message = "Hello, my name is Martin";
	std::string display = "";

	int index = 0;*/

	/* TIME
	
	sf::Clock clock;

	sf::Time time = clock.getElapsedTime();

	std::cout << time.asMilliseconds() << std::endl;*/

	int nextPose;

	nextPose = 0;

	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			/*if (Event.type == sf::Event::Closed)
				Window.close();*/

			switch (Event.type)
			{
			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Escape)
					Window.close();
				else if (Event.key.code == sf::Keyboard::LAlt)
					
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
			/*case sf::Event::LostFocus:
				std::cout << "Window NOT Active" << std::endl;
				break;
			case sf::Event::GainedFocus:
				std::cout << "Window IS Active" << std::endl;
				break;*/
			}

			/*if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::Return)
				{
					display += message[index];
					index++;
					system("cls");
					std::cout << display;
				}
			}*/
		}

		// First player movement

		float movement_speed = (float) 0.013;

		// Increasing movement speed

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			movement_speed *= 2;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			source1.y = Up;
			playerImage1.move(0, -movement_speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			source1.y = Down;
			playerImage1.move(0, movement_speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			source1.y = Left;
			playerImage1.move(-movement_speed, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			source1.y = Right;
			playerImage1.move(movement_speed, 0);
		}

		// Second player movement

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			source2.y = Up;
			playerImage2.move(0, -movement_speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			source2.y = Down;
			playerImage2.move(0, movement_speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			source2.y = Left;
			playerImage2.move(-movement_speed, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			source2.y = Right;
			playerImage2.move(movement_speed, 0);
		}

		/* waitEvent ceka na nejakou udalost a pullEvent veme udalost, ktera je na rade.
		
		if (Window.waitEvent(Event))
		{
			std::cout << "Event activated" << std::endl;
		}*/
		
		/* TIME

		time = clock.getElapsedTime();

		std::cout << time.asSeconds() << std::endl;

		clock.restart();*/

		if ( nextPose == 2000 )
		{
			source1.x++;
			source2.x++;
			nextPose = 0;
		}
		else nextPose++;
		
		if (source1.x * 32 >= pTexture1.getSize().x)
			source1.x = 0;

		if (source2.x * 32 >= pTexture2.getSize().x)
			source2.x = 0;

		playerImage1.setTextureRect(sf::IntRect(source1.x * 32, source1.y * 32, 32, 32));
		playerImage2.setTextureRect(sf::IntRect(source2.x * 32, source2.y * 32, 32, 32));

		Window.draw(playerImage1);
		Window.draw(playerImage2);
		Window.display();
		Window.clear();
	}
}