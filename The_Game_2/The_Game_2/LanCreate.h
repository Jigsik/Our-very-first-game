#ifndef __LANCREATE_H_INCLUDED__
#define __LANCREATE_H_INCLUDED__

#include <iostream>
#include "cScreen.h"
#include "VideoSettings.h"
#include "MenuManager.h"
#include "MenuScreen.h"
#include <SFML\Network.hpp>
#include "Client.h"
#include "LanServer.h"

class LanCreate : public cScreen, public MenuScreen
{
private:
	// Texts
	sf::Text IPAddressLabel;
	sf::Text connectedPlayersLabel;

	// Buttons
	Button startButton;
	Button backButton;

	void setButtonsSelected(int selectedButton);
	void draw(sf::RenderWindow &App);

	enum lanButton { START, BACK };

	int numberOfButtons = 2;
	int connectedPlayers = 0;
	int selectedButton = START;

	//sf::UdpSocket socket;
	unsigned short port;
	sf::IpAddress IPAddress;
	sf::TcpListener tcp_listener;

	std::vector<sf::TcpSocket*> clients;
	std::vector<sf::TcpSocket*>::iterator clientsIt;

public:
	LanCreate(VideoSettings *videoSettings);
	~LanCreate();
	virtual int Run(sf::RenderWindow &App);

	std::vector<Client*> udpClients;
	std::vector<Client*>::iterator udpClientsIt;
};

#endif // !__LANCREATE_H_INCLUDED__