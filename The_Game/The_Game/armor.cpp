#include "armor.h"
//#include <SFML\Graphics.hpp>
#include <iostream>

armor::armor(double _armor_hp)
: hp(_armor_hp)
{
	if (!pTexture.loadFromFile("Images/armor.png"))
		std::cout << "Error could not load player image 1" << std::endl;

	armorImage.setTexture(pTexture);

	std::cout << "Armor created" << std::endl;
}

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