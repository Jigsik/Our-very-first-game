#include "MainMenu.h"

MainMenu::MainMenu(VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	setBackground();

	// Add buttons to std::Vector
	buttons.push_back(&storyButton);
	buttons.push_back(&multiplayerButton);
	buttons.push_back(&settingsButton);
	buttons.push_back(&exitButton);

	// Set Buttons texts
	storyButton.initializeButton("Story", videoSettings);
	multiplayerButton.initializeButton("Multiplayer", videoSettings);
	settingsButton.initializeButton("Settings", videoSettings);
	exitButton.initializeButton("Exit", videoSettings);

	setButtons();

	numberOfButtons = 4;
	selectedButton = B_STORY;
}

int MainMenu::Run(sf::RenderWindow &App)
{
	while (true)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return -1;
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
					if (selectedButton < numberOfButtons - 1 && selectedButton >= 0)
					{
						if (selectedButton == B_MULTIPLAYER)
							return M_MULTIPLAYER;
					}
					else
						return -1;
					break;
				default:
					break;
				}
			}
		}

		selectButton();
		draw(App);
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}

void MainMenu::selectButton()
{
	setButtonsSelectedALL(false);

	if (selectedButton == B_STORY)
		storyButton.setSelected(true);
	else if (selectedButton == B_MULTIPLAYER)
		multiplayerButton.setSelected(true);
	else if (selectedButton == B_SETTINGS)
		settingsButton.setSelected(true);
	else if (selectedButton == B_EXIT)
		exitButton.setSelected(true);
	else std::cerr << "Error selecting button" << std::endl;
}