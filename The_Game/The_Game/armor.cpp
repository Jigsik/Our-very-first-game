#include "armor.h"
//#include <SFML\Graphics.hpp>
#include <iostream>

armor::armor(double _armor_hp)
: hp(_armor_hp)
{
	if (!pTexture.loadFromFile("Images/armor.png"))
		std::cout << "Error could not load player image 1" << std::endl;

	armorImage.setTexture(pTexture);

	if (!pTexture1.loadFromFile("Images/armor.png"))
		std::cout << "Error could not load player image 2" << std::endl;

	armorImage1.setTexture(pTexture1);

	std::cout << "Armor created" << std::endl;
}

/*void armor::draw(sf::RenderWindow* Window)
{
	armorImage.setPosition(hrac.playerImage.getPosition().x + 15, hrac.playerImage.getPosition().y + 15);
	armorImage1.setPosition(hrac.playerImage.getPosition().x + 15, hrac.playerImage.getPosition().y + 15);
}*/

armor::~armor()
{
	std::cout << "Armor destructed" << std::endl;
}

sf::Time armor::time_left()
{
	return time.getElapsedTime();
}

double armor::armor_left()
{
	return hp;
}