#include "LanClient.h"


LanClient::LanClient()
{
}


LanClient::~LanClient()
{
}

unsigned int LanClient::getPort()
{
	return socket.getLocalPort();
}

sf::IpAddress LanClient::getIPAddress()
{
	return sf::IpAddress::getLocalAddress();
}

void LanClient::setUDP()
{
	if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		std::cout << "Client socket ERROR" << std::endl;
	}
}