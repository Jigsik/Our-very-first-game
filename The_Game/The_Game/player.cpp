#include "player.h"
#include <SFML\Graphics.hpp>
#include <iostream>

player::player(double _hp, double _speed)
: HP(_hp), speed(_speed)
{
	if (!pTexture.loadFromFile("Images/player_1.png"))
		std::cout << "Error could not load player image." << std::endl;

	playerImage.setTexture(pTexture);

	std::cout << "Player created" << std::endl;
}

void player::HP_minus(double damaged)
{
	HP -= damaged;
}

double player::HP_left()
{
	return HP;
}