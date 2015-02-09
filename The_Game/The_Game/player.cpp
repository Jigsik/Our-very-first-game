#include "player.h"
#include <SFML\Graphics.hpp>
#include <iostream>

player::player(double _hp, float _speed)
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

int player::move()
{
	// It means - Down = 0, Left = 1, Right = 2, Up = 3

	enum Direction { Down, Left, Right, Up };

	// Movement speed

	speed = 1,5;

	// Increasing movement speed

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		speed *= 2;
	}

	// Player movement

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerImage.move(-speed, -speed);
		return Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerImage.move(speed, -speed);
		return Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerImage.move(speed, speed);
		return Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerImage.move(-speed, speed);
		return Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerImage.move(0, -speed);
		return Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		playerImage.move(0, speed);
		return Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerImage.move(-speed, 0);
		return Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerImage.move(speed, 0);
		return Right;
	}
}