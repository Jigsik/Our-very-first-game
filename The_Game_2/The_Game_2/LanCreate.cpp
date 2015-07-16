#include "LanCreate.h"


LanCreate::LanCreate(VideoSettings *videoSettings)
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

	IPAddressLabel.setFont(Font);
	IPAddressLabel.setCharacterSize(fontSize);
	IPAddressLabel.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	connectedPlayersLabel.setFont(Font);
	connectedPlayersLabel.setCharacterSize(fontSize);
	connectedPlayersLabel.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	startButton.setFont(Font);
	startButton.setCharacterSize(fontSize);
	startButton.setString("Start");
	startButton.setOrigin(startButton.getLocalBounds().width / 2, startButton.getLocalBounds().height / 2);
	startButton.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	backButton.setFont(Font);
	backButton.setCharacterSize(fontSize);
	backButton.setString("Back");
	backButton.setOrigin(backButton.getLocalBounds().width / 2, backButton.getLocalBounds().height / 2);
	backButton.setPosition(horizontalCenter, verticalPos);
}


LanCreate::~LanCreate()
{
	for (clientsIt = clients.begin(); clientsIt != clients.end();)
	{
		delete *clientsIt;
		clientsIt = clients.erase(clientsIt);
	}
}

int LanCreate::Run(sf::RenderWindow &App)
{
	/*// bind the socket to a port
	if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		// error...
	}*/

	// bind the listener to a port
	if (tcp_listener.listen(53000/*sf::Socket::AnyPort*/) != sf::Socket::Done)
	{
		// error...
	}

	port = tcp_listener.getLocalPort();
	IPAddress = sf::IpAddress::getLocalAddress();

	IPAddressLabel.setString(IPAddress.toString());
	IPAddressLabel.setOrigin(IPAddressLabel.getLocalBounds().width / 2, IPAddressLabel.getLocalBounds().height / 2);

	connectedPlayersLabel.setString(std::to_string(connectedPlayers));
	connectedPlayersLabel.setOrigin(connectedPlayersLabel.getLocalBounds().width / 2, connectedPlayersLabel.getLocalBounds().height / 2);

	tcp_listener.setBlocking(false);

	// accept a new connection
	while (true)
	{
		sf::TcpSocket* client = new sf::TcpSocket();
		sf::Socket::Status status;

		status = tcp_listener.accept(*client);

		if (status == sf::Socket::Done)
		{
			clients.push_back(client);
			connectedPlayers++;

			connectedPlayersLabel.setString(std::to_string(connectedPlayers));
			connectedPlayersLabel.setOrigin(connectedPlayersLabel.getLocalBounds().width / 2, connectedPlayersLabel.getLocalBounds().height / 2);
		}

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
						if (selectedButton == BACK) return 0;
						else if (selectedButton == START) return 3;
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

		if (selectedButton == START)
		{
			startButton.setColor(sf::Color(255, 0, 0, 255));
			backButton.setColor(sf::Color(255, 255, 255, 255));
		}
		else if (selectedButton == BACK)
		{
			startButton.setColor(sf::Color(255, 255, 255, 255));
			backButton.setColor(sf::Color(255, 0, 0, 255));
		}
		else std::cout << "SOMETHING IS WRONG WITH RED LABEL" << std::endl;

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(Sprite);
		App.draw(startButton);
		App.draw(IPAddressLabel);
		App.draw(connectedPlayersLabel);
		App.draw(backButton);
		App.display();
	}

	// use "client" to communicate with the connected client,
	// and continue to accept new connections with the listener
}
