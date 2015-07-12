#include "SpeedRune.h"

SpeedRune::SpeedRune(sf::Vector2u mapSize)
{
	setRune("Images/speed_rune.png", mapSize);

	type = speedRune;
};

SpeedRune::~SpeedRune(){

};