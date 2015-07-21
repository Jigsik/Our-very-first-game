#ifndef __LANSERVER_H_INCLUDED__
#define __LANSERVER_H_INCLUDED__

#include <iostream>
#include "Client.h"

class LanServer
{
private:
	std::vector<Client*> udpClients;
	std::vector<Client*>::iterator udpClientsIt;

public:
	LanServer();
	~LanServer();

	void addPlayer(sf::IpAddress IPAddress, int port);
};

#endif // !__LANSERVER_H_INCLUDED__