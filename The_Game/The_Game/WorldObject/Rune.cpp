#include "Rune.h"

Rune::Rune()
{
}

int Rune::getType()
{
	return type;
}

void Rune::setRune(std::string location, sf::Vector2u mapSize)
{
	if (!pTexture.loadFromFile(location))
		std::cout << "Error could not load rune image." << std::endl;

	image.setTexture(pTexture);

	int a1 = rand() % (mapSize.x - getSize().x);
	int a2 = rand() % (mapSize.y - getSize().y);

	image.setPosition(sf::Vector2f((float)a1, (float)a2));
}

int Rune::getDuration()
{
	return duration;
}

Rune::~Rune()
{
	std::cout << "Rune Destroyed" << std::endl;
}