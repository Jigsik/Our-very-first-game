#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <string>
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
	enemy nepritel;
	rocket_missile *raketa = 0;

	sf::Clock brneniClock;

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
					hrac.activateArmor();
				}
				else if (Event.key.code == sf::Keyboard::LControl)
				{
					raketa = new rocket_missile(hrac.playerImage.getPosition(), hrac.rocket_direction);
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

		// Raketa

		if (raketa)
		{
			raketa->draw(Window, nepritel.Image.getPosition());
		}
		
		if (fpsClock.getElapsedTime().asSeconds() > 1)
		{
			/* Z nìjakého dùvodu se hra sekne, když zavolám clear do pøíkazové øádky,
			takže to asi žere moc výkonu a z toho dùvodu to nelze použít. */
			// system("cls");

			//std::cout << "FPS = " << fps;

			std::ostringstream oss;
			oss << fps;
			fpsString = oss.str();

			//std::cout << ", Sound ends in: " << music.getDuration().asSeconds() - music.getPlayingOffset().asSeconds() << " seconds." << std::endl;

			fpsClock.restart();

			fps = 0;
		}
		else fps++;

		fpsText.setString(fpsString);

		Window->draw(fpsText);

		hrac.draw(Window);
		nepritel.draw(Window, hrac.playerImage.getPosition());

		Window->display();

		if (isPause)
		{
			pause(Window);

			isPause = false;
		}

		Window->clear();
	}

	delete raketa;
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