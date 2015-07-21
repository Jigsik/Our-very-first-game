#ifndef __LANCLIENT_H_INCLUDED__
#define __LANCLIENT_H_INCLUDED__

#include <SFML\Network.hpp>
#include <iostream>

class LanClient
{
private:
	unsigned int port;
	sf::UdpSocket socket;
public:
	LanClient();
	~LanClient();

	void setUDP();
	unsigned int getPort();
	sf::IpAddress getIPAddress();
};

#endif // !__LANCLIENT_H_INCLUDED__