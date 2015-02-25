#include "Armor1.h"

Armor::Armor()
{
	if (!pTexture.loadFromFile("Images/armor.png"))
		std::cout << "Error could not load armor image" << std::endl;

	image.setTexture(pTexture);
	image1.setTexture(pTexture);

	image.setOrigin((float)pTexture.getSize().x / 2, (float)pTexture.getSize().y / 2);
	image1.setOrigin((float)pTexture.getSize().x / 2, (float)pTexture.getSize().y / 2);

	// Before it was 0.8 instead of 1.2
	image1.setScale((float)1.2, (float)1.2);

	std::cout << "Armor created" << std::endl;
}

Armor::~Armor()
{
}

int Armor::getHP()
{
	return HP;
}

void Armor::changeState(sf::RenderWindow *Window, sf::Vector2f playerPosition, sf::Vector2u characterSize)
{
	// Set position
	image.setPosition(playerPosition.x + (characterSize.x / 2), playerPosition.y + (characterSize.y / 2));
	image1.setPosition(playerPosition.x + (characterSize.x / 2), playerPosition.y + (characterSize.y / 2));

	// Rotate
	if (rotateClock.getElapsedTime().asMilliseconds() > 10)
	{
		image.rotate(1);
		image1.rotate(-1);

		rotateClock.restart();
	}

	// text

	text.setPosition(sf::Vector2f((float)Window->getSize().x - 200, 0));

	string = std::to_string(10 - (int)clock.getElapsedTime().asSeconds());

	text.setString("Armor: " + string + "s");

	// KOnec TEXT
	Window->setView(Window->getDefaultView());

	Window->draw(text);
}