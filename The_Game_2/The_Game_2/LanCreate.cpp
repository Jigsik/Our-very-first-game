#include "LanCreate.h"

LanCreate::LanCreate(VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	if (!setBackground())
		; // TODO : Throw exception

	if (!setFont())
		; // TODO : Throw exception
	
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

	startButton.initializeButton("Start", videoSettings);
	startButton.setOrigin("CENTER", "CENTER");
	startButton.setPosition(startButton.HORIZONTALCENTER, verticalPos);

	verticalPos += verticalRatio;

	backButton.initializeButton("Back", videoSettings);
	backButton.setOrigin("CENTER", "CENTER");
	backButton.setPosition(backButton.HORIZONTALCENTER, verticalPos);
}

LanCreate::~LanCreate()
{
	for (clientsIt = clients.begin(); clientsIt != clients.end();)
	{
		delete *clientsIt;
		clientsIt = clients.erase(clientsIt);
	}

	//tcp_listener.close();
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

		for (clientsIt = clients.begin(); clientsIt != clients.end();)
		{
			//std::cout << "checking connected clients" << std::endl;

			char check = 0;

			if ((*clientsIt)->send(&check, 1) == sf::TcpSocket::Status::Disconnected)
			{
				delete *clientsIt;
				clientsIt = clients.erase(clientsIt);
				connectedPlayers--;

				std::cout << "PLAYER LEFT" << std::endl;

				connectedPlayersLabel.setString(std::to_string(connectedPlayers));
				connectedPlayersLabel.setOrigin(connectedPlayersLabel.getLocalBounds().width / 2, connectedPlayersLabel.getLocalBounds().height / 2);
			}
			else clientsIt++;
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
						if (selectedButton == BACK)
						{
							tcp_listener.close();
							return X_LAN;
						}
						else if (selectedButton == START)
						{
							// Is anyone connected?
							if (clients.size() == 0)
							{
								std::cout << "No one is connected.." << std::endl;
								break;
							}

							std::cout << "HEEEH" << std::endl;

							// set UDP clients
							// it is going to move to another class

							char start = 1;

							for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
							{
								if ((*clientsIt)->send(&start, 1) != sf::TcpSocket::Status::Done)
								{
									std::cout << "Error starting game" << std::endl;
								}
							}

							for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
							{
								bool clientMessage;
								std::size_t received;

								if ((*clientsIt)->receive(&clientMessage, 1, received) == sf::Socket::Done)
								{
									if (clientMessage)
										std::cout << "PLAYER IS READY" << std::endl;
									else if (!clientMessage)
									{
										std::cout << "PLAYER IS NOT READY" << std::endl;
									}
								}
							}

							LanServer game;

							for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
							{

								// NEED LANCLIENT
								//game.addPlayer((*clientsIt)->getRemoteAddress(), );

								/*Client* udpClient = new Client();

								udpClient->setIPAddress((*clientsIt)->getRemoteAddress());
								//udpClient->setPort = (*clientsIt)->getRemotePort();

								udpClients.push_back(udpClient);*/
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

		setButtonsSelected(selectedButton);

		draw(App);
	}

	// use "client" to communicate with the connected client,
	// and continue to accept new connections with the listener
}

void LanCreate::setButtonsSelected(int selectedButton)
{
	startButton.setSelected(false);
	backButton.setSelected(false);

	if (selectedButton == START)
		startButton.setSelected(true);
	else if (selectedButton == BACK)
		backButton.setSelected(true);
	else std::cout << "SOMETHING IS WRONG WITH RED LABEL" << std::endl;
}

void LanCreate::draw(sf::RenderWindow &App)
{
	//Clearing screen
	App.clear();

	//Drawing
	App.draw(backgroundImage);
	App.draw(startButton);
	App.draw(IPAddressLabel);
	App.draw(connectedPlayersLabel);
	App.draw(backButton);
	App.display();
}