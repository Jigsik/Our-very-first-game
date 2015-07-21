#include "LanServer.h"

LanServer::LanServer()
{
}

LanServer::~LanServer()
{
	for (udpClientsIt = udpClients.begin(); udpClientsIt != udpClients.end();)
	{
		delete *udpClientsIt;
		udpClientsIt = udpClients.erase(udpClientsIt);
	}
}

void LanServer::addPlayer(sf::IpAddress IPAddress, int port)
{
	Client* player = new Client();
	player->setIPAddress(IPAddress);
	player->setPort(port);
	udpClients.push_back(player);
}