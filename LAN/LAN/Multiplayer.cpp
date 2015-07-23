#include "Multiplayer.h"

Multiplayer::Multiplayer(VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	setBackground();

	// Add buttons to std::Vector
	buttons.push_back(&splitScreenButton);
	buttons.push_back(&lanButton);
	buttons.push_back(&backButton);

	// Set Buttons texts
	splitScreenButton.initializeButton("Splitscreen", videoSettings);
	lanButton.initializeButton("LAN", videoSettings);
	backButton.initializeButton("Back", videoSettings);

	setButtons();

	numberOfButtons = 3;
	selectedButton = B_SPLITSCREEN;
}

int Multiplayer::Run(sf::RenderWindow &App)
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
					if (selectedButton < numberOfButtons && selectedButton >= 0)
					{
						if (selectedButton == B_BACK) return M_MAIN;
						else if (selectedButton == B_SPLITSCREEN) return 0; // TODO
						else if (selectedButton == B_LAN) return M_LAN;
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

void Multiplayer::selectButton()
{
	setButtonsSelectedALL(false);

	if (selectedButton == B_SPLITSCREEN)
		splitScreenButton.setSelected(true);
	else if (selectedButton == B_LAN)
		lanButton.setSelected(true);
	else if (selectedButton == B_BACK)
		backButton.setSelected(true);
	else std::cerr << "Error selecting button" << std::endl;
}