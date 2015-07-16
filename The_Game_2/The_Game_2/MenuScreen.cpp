#include "MenuScreen.h"

MenuScreen::MenuScreen(VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	if (!Texture.loadFromFile("Images/menuPic.jpg"))
	{
		std::cerr << "Error loading menuPic" << std::endl;
		// Throw an exception
	}
	Sprite.setTexture(Texture);
	Sprite.setScale(
		videoSettings->getScreenDimensions().x / Sprite.getLocalBounds().width,
		videoSettings->getScreenDimensions().y / Sprite.getLocalBounds().height);

	if (!Font.loadFromFile("Fonts/STENCIL.ttf"))
	{
		std::cerr << "Error loading STENCIL.ttf" << std::endl;
		// Throw an exception
	}

	int fontSize = videoSettings->getScreenDimensions().y / 10;
	float horizontalCenter = (float)videoSettings->getScreenDimensions().x / 2;
	float verticalPos = (float)videoSettings->getScreenDimensions().y / 5;
	float verticalRatio = (float)videoSettings->getScreenDimensions().y / 5;

	storyButton.setFont(Font);
	storyButton.setCharacterSize(fontSize);
	storyButton.setString("Story");
	storyButton.setOrigin(storyButton.getLocalBounds().width / 2, storyButton.getLocalBounds().height / 2);
	storyButton.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	multiplayerButton.setFont(Font);
	multiplayerButton.setCharacterSize(fontSize);
	multiplayerButton.setString("Multiplayer");
	multiplayerButton.setOrigin(multiplayerButton.getLocalBounds().width / 2, multiplayerButton.getLocalBounds().height / 2);
	multiplayerButton.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	settingsButton.setFont(Font);
	settingsButton.setCharacterSize(fontSize);
	settingsButton.setString("Settings");
	settingsButton.setOrigin(settingsButton.getLocalBounds().width / 2, settingsButton.getLocalBounds().height / 2);
	settingsButton.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	exitButton.setFont(Font);
	exitButton.setCharacterSize(fontSize);
	exitButton.setString("Exit");
	exitButton.setOrigin(exitButton.getLocalBounds().width / 2, exitButton.getLocalBounds().height / 2);
	exitButton.setPosition(horizontalCenter, verticalPos);
}

int MenuScreen::Run(sf::RenderWindow &App)
{
	while (Running)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Up:
					if (menu > 0) menu--;
					break;
				case sf::Keyboard::Down:
					if (menu < numberOfButtons - 1) menu++;
					break;
				case sf::Keyboard::A:
					videoSettings->setScreenDimensions(videoSettings->getScreenDimensions().x + 1, videoSettings->getScreenDimensions().y + 1);
					App.setSize(videoSettings->getScreenDimensions());
					break;
				case sf::Keyboard::Return:
					if (menu < 3 && menu >= 0)
					{
						std::cout << "HMMM" << std::endl;
						return menu;
					}
					else
					{
						//Let's get work...
						return (-1);
					}
					break;
				default:
					break;
				}
			}
		}

		if (menu == STORY)
		{
			storyButton.setColor(sf::Color(255, 0, 0, 255));
			multiplayerButton.setColor(sf::Color(255, 255, 255, 255));
			settingsButton.setColor(sf::Color(255, 255, 255, 255));
			exitButton.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (menu == MULTIPLAYER)
		{
			storyButton.setColor(sf::Color(255, 255, 255, 255));
			multiplayerButton.setColor(sf::Color(255, 0, 0, 255));
			settingsButton.setColor(sf::Color(255, 255, 255, 255));
			exitButton.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (menu == SETTINGS)
		{
			storyButton.setColor(sf::Color(255, 255, 255, 255));
			multiplayerButton.setColor(sf::Color(255, 255, 255, 255));
			settingsButton.setColor(sf::Color(255, 0, 0, 255));
			exitButton.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (menu == EXIT)
		{
			storyButton.setColor(sf::Color(255, 255, 255, 255));
			multiplayerButton.setColor(sf::Color(255, 255, 255, 255));
			settingsButton.setColor(sf::Color(255, 255, 255, 255));
			exitButton.setColor(sf::Color(255, 0, 0, 255));
		}
		else std::cout << "SOMETHING IS WRONG WITH RED LABEL" << std::endl;

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(Sprite);
		App.draw(storyButton);
		App.draw(multiplayerButton);
		App.draw(settingsButton);
		App.draw(exitButton);
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}