#ifndef __CLIENT_H_INCLUDED__
#define __CLIENT_H_INCLUDED__

#include <SFML\Network.hpp>

class Client
{
private:
	sf::IpAddress ipAddress;
	unsigned int port;

public:
	Client();
	~Client();

	void setIPAddress(sf::IpAddress ipAddress);
	void setPort(unsigned int port);

	sf::IpAddress getIPAddress();
	unsigned int getPort();
};

#endif // !__CLIENT_H_INCLUDED__