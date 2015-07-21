#include "MainMenu.h"

MainMenu::MainMenu(VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	if (!setBackground())
		; // TODO : Throw exception

	//float horizontalCenter = (float)videoSettings->getScreenDimensions().x / 2;
	float verticalPos = (float)videoSettings->getScreenDimensions().y / 5;
	float verticalRatio = (float)videoSettings->getScreenDimensions().y / 5;

	storyButton.initializeButton("Story", videoSettings);
	storyButton.setOrigin("CENTER", "CENTER");
	storyButton.setPosition(storyButton.HORIZONTALCENTER, verticalPos);

	verticalPos += verticalRatio;

	multiplayerButton.initializeButton("Multiplayer", videoSettings);
	multiplayerButton.setOrigin("CENTER", "CENTER");
	multiplayerButton.setPosition(multiplayerButton.HORIZONTALCENTER, verticalPos);

	verticalPos += verticalRatio;

	settingsButton.initializeButton("Settings", videoSettings);
	settingsButton.setOrigin("CENTER", "CENTER");
	settingsButton.setPosition(settingsButton.HORIZONTALCENTER, verticalPos);

	verticalPos += verticalRatio;

	exitButton.initializeButton("Exit", videoSettings);
	exitButton.setOrigin("CENTER", "CENTER");
	exitButton.setPosition(exitButton.HORIZONTALCENTER, verticalPos);
}

int MainMenu::Run(sf::RenderWindow &App)
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
					if (selectedButton > 0) selectedButton--;
					break;
				case sf::Keyboard::Down:
					if (selectedButton < numberOfButtons - 1) selectedButton++;
					break;
				//case sf::Keyboard::A:
					//videoSettings->setScreenDimensions(videoSettings->getScreenDimensions().x + 1, videoSettings->getScreenDimensions().y + 1);
					//App.setSize(videoSettings->getScreenDimensions());
					//break;
				case sf::Keyboard::Return:
					if (selectedButton < numberOfButtons - 1 && selectedButton >= 0)
						return selectedButton;
					else
						return -1;
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

void MainMenu::setButtonsSelected(int selectedButtons)
{
	storyButton.setSelected(false);
	multiplayerButton.setSelected(false);
	settingsButton.setSelected(false);
	exitButton.setSelected(false);

	if (selectedButton == STORY)
		storyButton.setSelected(true);
	else if (selectedButton == MULTIPLAYER)
		multiplayerButton.setSelected(true);
	else if (selectedButton == SETTINGS)
		settingsButton.setSelected(true);
	else if (selectedButton == EXIT)
		exitButton.setSelected(true);
	else std::cout << "SOMETHING IS WRONG WITH RED LABEL" << std::endl;
}

void MainMenu::draw(sf::RenderWindow &App)
{
	//Clearing screen
	App.clear();

	//Drawing
	App.draw(backgroundImage);
	App.draw(storyButton);
	App.draw(multiplayerButton);
	App.draw(settingsButton);
	App.draw(exitButton);
	App.display();
}