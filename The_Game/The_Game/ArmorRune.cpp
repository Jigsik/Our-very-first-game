#include "WorldObject\ArmorRune.h"

ArmorRune::ArmorRune(sf::Vector2u mapSize)
{
	setRune("Images/armor_rune.png", mapSize);

	type = armorRune;
};

ArmorRune::~ArmorRune(){

};