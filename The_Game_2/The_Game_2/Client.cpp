#include "Client.h"


Client::Client()
{
}


Client::~Client()
{
}

void Client::setIPAddress(sf::IpAddress ipAddress)
{
	this->ipAddress = ipAddress;
}

void Client::setPort(unsigned int port)
{
	this->port = port;
}

sf::IpAddress Client::getIPAddress()
{
	return ipAddress;
}

unsigned int Client::getPort()
{
	return port;
}