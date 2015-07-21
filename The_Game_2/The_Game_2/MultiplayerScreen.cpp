#include "MultiplayerScreen.h"

MultiplayerScreen::MultiplayerScreen(VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	if (!setBackground())
		; // TODO : Throw exception

	//float horizontalCenter = (float)videoSettings->getScreenDimensions().x / 2;
	float verticalPos = (float)videoSettings->getScreenDimensions().y / 5;
	float verticalRatio = (float)videoSettings->getScreenDimensions().y / 5;

	splitScreenButton.initializeButton("Splitscreen", videoSettings);
	splitScreenButton.setOrigin("CENTER", "CENTER");
	splitScreenButton.setPosition(splitScreenButton.HORIZONTALCENTER, verticalPos);

	verticalPos += verticalRatio;

	lanButton.initializeButton("LAN", videoSettings);
	lanButton.setOrigin("CENTER", "CENTER");
	lanButton.setPosition(lanButton.HORIZONTALCENTER, verticalPos);

	verticalPos += verticalRatio;

	backButton.initializeButton("Back", videoSettings);
	backButton.setOrigin("CENTER", "CENTER");
	backButton.setPosition(backButton.HORIZONTALCENTER, verticalPos);
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
					if (selectedButton < numberOfButtons && selectedButton >= 0)
					{
						if (selectedButton == BACK) return X_MAIN;
						else if (selectedButton == SPLITSCREEN) return 0;
						else if (selectedButton == LAN) return X_LAN;
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

void MultiplayerScreen::setButtonsSelected(int selectedButton)
{
	splitScreenButton.setSelected(false);
	lanButton.setSelected(false);
	backButton.setSelected(false);

	if (selectedButton == SPLITSCREEN)
		splitScreenButton.setSelected(true);
	else if (selectedButton == LAN)
		lanButton.setSelected(true);
	else if (selectedButton == BACK)
		backButton.setSelected(true);
	else std::cout << "SOMETHING IS WRONG WITH RED LABEL" << std::endl;
}

void MultiplayerScreen::draw(sf::RenderWindow &App)
{
	//Clearing screen
	App.clear();

	//Drawing
	App.draw(backgroundImage);
	App.draw(splitScreenButton);
	App.draw(lanButton);
	App.draw(backButton);
	App.display();
}