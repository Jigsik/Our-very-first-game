#ifndef __LANJOIN_H_INCLUDED__
#define __LANJOIN_H_INCLUDED__

#include <iostream>
#include "cScreen.h"
#include "VideoSettings.h"
#include "MenuManager.h"
#include "MenuScreen.h"
#include <SFML\Network.hpp>

class LanJoin : public cScreen, public MenuScreen
{
private:
	// Buttons
	Button readyButton;
	Button leaveButton;

	void setButtonsSelected(int selectedButton);
	void draw(sf::RenderWindow &App);

	enum joinButton { READY, LEAVE };

	int numberOfButtons = 2;
	int selectedButton = READY;
	bool ready = false;

	// Network
	sf::TcpSocket socket;
	sf::Socket::Status status;
	sf::IpAddress IPAddress = "192.168.0.128";
	unsigned port = 53000;
public:
	LanJoin(VideoSettings *videoSettings);
	~LanJoin();
	virtual int Run(sf::RenderWindow &App);
};

#endif // !__LANJOIN_H_INCLUDED__