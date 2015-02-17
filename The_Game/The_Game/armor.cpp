#include "Armor.h"
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

void armor::draw(sf::RenderWindow* Window, sf::Vector2f playerPosition, sf::Vector2u characterSize)
{
	armorImage.setOrigin((float)pTexture.getSize().x / 2, (float)pTexture.getSize().y / 2);
	armorImage1.setOrigin((float)pTexture.getSize().x / 2, (float)pTexture.getSize().y / 2);

	armorImage.setPosition(playerPosition.x + (characterSize.x / 2), playerPosition.y + (characterSize.y / 2));
	armorImage1.setPosition(playerPosition.x + (characterSize.x / 2), playerPosition.y + (characterSize.y / 2));

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