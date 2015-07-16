#ifndef __LANCREATE_H_INCLUDED__
#define __LANCREATE_H_INCLUDED__

#include <iostream>
#include "cScreen.h"
#include "VideoSettings.h"
#include <SFML\Network.hpp>

class LanCreate : public cScreen
{
private:
	// Settings
	VideoSettings *videoSettings;

	// Texts
	sf::Text IPAddressLabel;
	sf::Text connectedPlayersLabel;

	// Buttons
	sf::Text startButton;
	sf::Text backButton;

	enum lanButton { START, BACK };

	// Background

	sf::Texture Texture;
	sf::Sprite Sprite;

	sf::Event Event;
	sf::Font Font;
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
};

#endif // !__LANCREATE_H_INCLUDED__