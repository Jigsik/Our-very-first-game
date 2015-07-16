#include "MultiplayerScreen.h"


MultiplayerScreen::MultiplayerScreen(VideoSettings *videoSettings)
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

	splitScreenButton.setFont(Font);
	splitScreenButton.setCharacterSize(fontSize);
	splitScreenButton.setString("Splitscreen");
	splitScreenButton.setOrigin(splitScreenButton.getLocalBounds().width / 2, splitScreenButton.getLocalBounds().height / 2);
	splitScreenButton.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	lanButton.setFont(Font);
	lanButton.setCharacterSize(fontSize);
	lanButton.setString("LAN");
	lanButton.setOrigin(lanButton.getLocalBounds().width / 2, lanButton.getLocalBounds().height / 2);
	lanButton.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	backButton.setFont(Font);
	backButton.setCharacterSize(fontSize);
	backButton.setString("Back");
	backButton.setOrigin(backButton.getLocalBounds().width / 2, backButton.getLocalBounds().height / 2);
	backButton.setPosition(horizontalCenter, verticalPos);
}


MultiplayerScreen::~MultiplayerScreen()
{
}

int MultiplayerScreen::Run(sf::RenderWindow &App)
{
	while (true)
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
					if (selectedButton > 0) selectedButton--;
					break;
				case sf::Keyboard::Down:
					if (selectedButton < numberOfButtons - 1) selectedButton++;
					break;
				case sf::Keyboard::Return:
					if (selectedButton < 3 && selectedButton >= 0)
					{
						if (selectedButton == BACK) return 0;
						else if (selectedButton == SPLITSCREEN) return 3;
						else if (selectedButton == LAN) return 4;
						else std::cout << "CHYBA" << std::endl;
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

		if (selectedButton == SPLITSCREEN)
		{
			splitScreenButton.setColor(sf::Color(255, 0, 0, 255));
			lanButton.setColor(sf::Color(255, 255, 255, 255));
			backButton.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (selectedButton == LAN)
		{
			splitScreenButton.setColor(sf::Color(255, 255, 255, 255));
			lanButton.setColor(sf::Color(255, 0, 0, 255));
			backButton.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (selectedButton == BACK)
		{
			splitScreenButton.setColor(sf::Color(255, 255, 255, 255));
			lanButton.setColor(sf::Color(255, 255, 255, 255));
			backButton.setColor(sf::Color(255, 0, 0, 255));
		}
		else std::cout << "SOMETHING IS WRONG WITH RED LABEL" << std::endl;

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(Sprite);
		App.draw(splitScreenButton);
		App.draw(lanButton);
		App.draw(backButton);
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}