#include "LanMenuScreen.h"

LanMenuScreen::LanMenuScreen(VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	if (!setBackground())
		; // TODO : Throw exception

	float horizontalCenter = (float)videoSettings->getScreenDimensions().x / 2;
	float verticalPos = (float)videoSettings->getScreenDimensions().y / 5;
	float verticalRatio = (float)videoSettings->getScreenDimensions().y / 5;

	createButton.initializeButton("Create a game", videoSettings);
	createButton.setOrigin("CENTER", "CENTER");
	createButton.setPosition(createButton.HORIZONTALCENTER, verticalPos);

	verticalPos += verticalRatio;

	joinButton.initializeButton("Join a game", videoSettings);
	joinButton.setOrigin("CENTER", "CENTER");
	joinButton.setPosition(joinButton.HORIZONTALCENTER, verticalPos);

	verticalPos += verticalRatio;

	backButton.initializeButton("Back", videoSettings);
	backButton.setOrigin("CENTER", "CENTER");
	backButton.setPosition(backButton.HORIZONTALCENTER, verticalPos);
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
					if (selectedButton < numberOfButtons && selectedButton >= 0)
					{
						if (selectedButton == BACK) return X_MULTIPLAYER;
						else if (selectedButton == CREATE)
						{
							/*LanCreate screen(videoSettings);
							int code = screen.Run(App);

							if (code == 1)
							{
								for (clientsIt = screen.udpClients.begin(); clientsIt != screen.udpClients.end(); clientsIt++)
								{
									connectedPlayers.push_back(*clientsIt);
								}
							}*/

							return X_LANCREATE;
						}
						else if (selectedButton == JOIN) return X_LANJOIN;
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

		setButtonsSelected(selectedButton);

		draw(App);
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}

void LanMenuScreen::setButtonsSelected(int selected)
{
	createButton.setSelected(false);
	joinButton.setSelected(false);
	backButton.setSelected(false);

	if (selectedButton == CREATE)
		createButton.setSelected(true);
	else if (selectedButton == JOIN)
		joinButton.setSelected(true);
	else if (selectedButton == BACK)
		backButton.setSelected(true);
	else std::cout << "SOMETHING IS WRONG WITH RED LABEL" << std::endl;
}

void LanMenuScreen::draw(sf::RenderWindow &App)
{
	//Clearing screen
	App.clear();

	//Drawing
	App.draw(backgroundImage);
	App.draw(createButton);
	App.draw(joinButton);
	App.draw(backButton);
	App.display();
}