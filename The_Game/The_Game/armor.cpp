#include "armor.h"
//#include <SFML\Graphics.hpp>
#include <iostream>

armor::armor(double _armor_hp)
: hp(_armor_hp)
{
	if (!pTexture.loadFromFile("Images/armor.png"))
		std::cout << "Error could not load player image 1" << std::endl;

	armorImage.setTexture(pTexture);
	armorImage1.setTexture(pTexture);

	std::cout << "Armor created" << std::endl;
}

void armor::draw(sf::RenderWindow* Window, sf::Vector2f playerPosition)
{
	armorImage.setPosition(playerPosition.x + 16, playerPosition.y + 16);
	armorImage1.setPosition(playerPosition.x + 16, playerPosition.y + 16);

	armorImage.setOrigin(28.5, 28.5);
	armorImage1.setOrigin(28.5, 28.5);

	armorImage1.setScale((float)0.8, (float)0.8);

	if (rotateClock.getElapsedTime().asMilliseconds() > 10)
	{
		armorImage.rotate(1);
		armorImage1.rotate(-1);

		rotateClock.restart();
	}

	Window->draw(armorImage);
	Window->draw(armorImage1);
}

armor::~armor()
{
	std::cout << "Armor destructed" << std::endl;
}

sf::Time armor::getTime()
{
	return time.getElapsedTime();
}

double armor::getHP()
{
	return hp;
}