#include "LanJoin.h"

LanJoin::LanJoin(VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	if (!setBackground())
		; // TODO : Throw exception

	//if (!setFont())
		//; // TODO : Throw exception

	//float horizontalCenter = (float)videoSettings->getScreenDimensions().x / 2;
	float verticalPos = (float)videoSettings->getScreenDimensions().y / 5;
	float verticalRatio = (float)videoSettings->getScreenDimensions().y / 5;

	readyButton.initializeButton("Ready", videoSettings);
	readyButton.setOrigin("CENTER", "CENTER");
	readyButton.setPosition(readyButton.HORIZONTALCENTER, verticalPos);

	verticalPos += verticalRatio;

	leaveButton.initializeButton("Leave", videoSettings);
	leaveButton.setOrigin("CENTER", "CENTER");
	leaveButton.setPosition(leaveButton.HORIZONTALCENTER, verticalPos);
}

LanJoin::~LanJoin()
{
}

int LanJoin::Run(sf::RenderWindow &App)
{
	// when the socket is set as non-blocking
	// it wont init too fast
	socket.setBlocking(true);

	sf::Socket::Status status = socket.connect(IPAddress, port);
	if (status != sf::Socket::Done)
	{
		std::cout << "Could not connect to a server" << std::endl;
		return X_LAN;
	}
	
	while (true)
	{
		char serverMessage;
		std::size_t received;

		if (socket.receive(&serverMessage, 1, received) == sf::Socket::Done)
		{
			if (serverMessage == 1)
				socket.send(&ready, 1);
		}

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
						if (selectedButton == LEAVE)
						{
							socket.disconnect();
							return X_LAN;
						}
						else if (selectedButton == READY)
							ready = !ready;
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
}

void LanJoin::setButtonsSelected(int selectedButton)
{
	readyButton.setSelected(false);
	leaveButton.setSelected(false);

	if (selectedButton == READY)
		readyButton.setSelected(true);
	else if (selectedButton == LEAVE)
		leaveButton.setSelected(true);
	else std::cout << "SOMETHING IS WRONG WITH RED LABEL" << std::endl;
}

void LanJoin::draw(sf::RenderWindow &App)
{
	//Clearing screen
	App.clear();

	//Drawing
	App.draw(backgroundImage);
	App.draw(readyButton);
	App.draw(leaveButton);
	App.display();
}