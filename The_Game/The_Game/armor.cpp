#include "armor.h"
//#include <SFML\Graphics.hpp>
#include <iostream>

armor::armor(double _armor_hp)
: armor_hp(_armor_hp)
{
	std::cout << "Armor created" << std::endl;
}

armor::~armor()
{
	std::cout << "Armor destructed" << std::endl;
	armor_time.restart();
}

sf::Time armor::time_left()
{
	return armor_time.getElapsedTime();
}