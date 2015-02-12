#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <string>
#include "player.h"
#include "Armor.h"
#include "enemy.h"
#include "rocket_missiles.h"

void game(sf::RenderWindow* Window)
{
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
	enemy nepritel;
	armor *brneni = 0;
	rocket_missile *raketa = 0;

	int fps = 0;
	sf::Clock fpsClock;

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
					//Window->close();

					return;
				}
				else if (Event.key.code == sf::Keyboard::LAlt)
				{
					brneni = new armor;
				}
				else if (Event.key.code == sf::Keyboard::LControl)
				{
					raketa = new rocket_missile(hrac.playerImage.getPosition(), hrac.rocket_direction);
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
			/* Z n�jak�ho d�vodu se hra sekne, kdy� zavol�m clear do p��kazov� ��dky,
			tak�e to asi �ere moc v�konu a z toho d�vodu to nelze pou��t. */
			// system("cls");

			std::cout << "FPS = " << fps;

			std::cout << ", Sound ends in: " << music.getDuration().asSeconds() - music.getPlayingOffset().asSeconds() << " seconds." << std::endl;

			fpsClock.restart();

			fps = 0;
		}
		else fps++;
	}

	delete brneni;
	delete raketa;
}

void menu()
{
	// Z nejakeho duvodu hlasi AVAST virus pri tomto volani.
	sf::RenderWindow *Window = 0;
	Window = new sf::RenderWindow;
	Window->create(sf::VideoMode(600, 400), "Hovnocuc");

	enum choice { newGame, konec };

	int active = newGame;
	int choiceCount = 2;

	sf::Font menuFont;
	
	if (!menuFont.loadFromFile("Fonts/HARNGTON.ttf"))
		std::cout << "Cannot load font for Menu" << std::endl;

	sf::String new_game = "NEW GAME";
	sf::String exit = "EXIT";

	sf::Text nova_hra;
	sf::Text konec_hry;
	nova_hra.setString(new_game);
	konec_hry.setString(exit);
	nova_hra.setFont(menuFont);
	konec_hry.setFont(menuFont);

	nova_hra.setPosition(sf::Vector2f((float)Window->getSize().x / 5, (float)Window->getSize().y / 5));
	konec_hry.setPosition(sf::Vector2f((float)Window->getSize().x / 5, (float)Window->getSize().y / 3));

	while (Window->isOpen())
	{
		sf::Event Event;

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

			konec_hry.setColor(sf::Color::Blue);
		}
		else if (active == 1)
		{
			konec_hry.setColor(sf::Color::Yellow);
			konec_hry.setStyle(sf::Text::Bold | sf::Text::Underlined);

			nova_hra.setColor(sf::Color::Blue);
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