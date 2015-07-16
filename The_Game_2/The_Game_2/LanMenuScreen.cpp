#include "LanMenuScreen.h"


LanMenuScreen::LanMenuScreen(VideoSettings *videoSettings)
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

	createButton.setFont(Font);
	createButton.setCharacterSize(fontSize);
	createButton.setString("Create a game");
	createButton.setOrigin(createButton.getLocalBounds().width / 2, createButton.getLocalBounds().height / 2);
	createButton.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	joinButton.setFont(Font);
	joinButton.setCharacterSize(fontSize);
	joinButton.setString("Join a game");
	joinButton.setOrigin(joinButton.getLocalBounds().width / 2, joinButton.getLocalBounds().height / 2);
	joinButton.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	backButton.setFont(Font);
	backButton.setCharacterSize(fontSize);
	backButton.setString("Back");
	backButton.setOrigin(backButton.getLocalBounds().width / 2, backButton.getLocalBounds().height / 2);
	backButton.setPosition(horizontalCenter, verticalPos);
}


LanMenuScreen::~LanMenuScreen()
{
}

int LanMenuScreen::Run(sf::RenderWindow &App)
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
						if (selectedButton == BACK) return 1;
						else if (selectedButton == CREATE) return 5;
						else if (selectedButton == JOIN)
						{
							sf::TcpSocket socket;
							sf::Socket::Status status = socket.connect("192.168.0.128", 53000);
							if (status != sf::Socket::Done)
							{
								// error...
							}


						}
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

		if (selectedButton == CREATE)
		{
			createButton.setColor(sf::Color(255, 0, 0, 255));
			joinButton.setColor(sf::Color(255, 255, 255, 255));
			backButton.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (selectedButton == JOIN)
		{
			createButton.setColor(sf::Color(255, 255, 255, 255));
			joinButton.setColor(sf::Color(255, 0, 0, 255));
			backButton.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (selectedButton == BACK)
		{
			createButton.setColor(sf::Color(255, 255, 255, 255));
			joinButton.setColor(sf::Color(255, 255, 255, 255));
			backButton.setColor(sf::Color(255, 0, 0, 255));
		}
		else std::cout << "SOMETHING IS WRONG WITH RED LABEL" << std::endl;

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(Sprite);
		App.draw(createButton);
		App.draw(joinButton);
		App.draw(backButton);
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}