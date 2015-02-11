#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <string>
#include "player.h"
#include "Armor.h"
#include "enemy.h"
#include "rocket_missiles.h"

int main()
{
	// Sound

	sf::Music music;

	if (!music.openFromFile("Sounds/music.wav"))
	{
		std::cout << "Unable to load music." << std::endl;
	}

	music.setLoop(true);
	music.play();

	player hrac;
	enemy nepritel;
	armor *brneni = 0;
	rocket_missile *raketa = 0;

	int fps = 0;
	sf::Clock fpsClock;

	// Z nejakeho duvodu hlasi AVAST virus pri tomto volani.
	sf::RenderWindow *Window = 0;
	Window = new sf::RenderWindow;
	Window->create(sf::VideoMode(600, 400), "Hovnocuc");

	//Window.setFramerateLimit(100);

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
					Window->close();
				}
				else if (Event.key.code == sf::Keyboard::LAlt)
				{
					brneni = new armor;
				}
				else if (Event.key.code == sf::Keyboard::LControl)
				{
					raketa = new rocket_missile(hrac.playerImage.getPosition());
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

		if (raketa)
		{
			raketa->draw(Window, nepritel.Image.getPosition());
		}

		if (brneni && brneni->time_left().asSeconds() > 10) 
		{
			brneni->~armor();
			brneni = 0;
		}
		else if (brneni) // Else draw armor
		{
			brneni->armorImage.setPosition(hrac.playerImage.getPosition().x - 10, hrac.playerImage.getPosition().y - 10);

			Window->draw(brneni->armorImage);
		}
		hrac.draw(Window);
		nepritel.draw(Window, hrac.playerImage.getPosition());
		Window->display();
		Window->clear();

		if (fpsClock.getElapsedTime().asSeconds() > 1)
		{
			/* Z nìjakého dùvodu se hra sekne, když zavolám clear do pøíkazové øádky,
			   takže to asi žere moc výkonu a z toho dùvodu to nelze použít. */
			// system("cls");

			std::cout << "FPS = " << fps;

			std::cout << ", Sound ends in: " << music.getDuration().asSeconds() - music.getPlayingOffset().asSeconds() << " seconds." << std::endl;

			fpsClock.restart();

			fps = 0;
		}
		else fps++;
	}

	Window->~RenderWindow();

	delete brneni;
	delete Window;
	delete raketa;
}