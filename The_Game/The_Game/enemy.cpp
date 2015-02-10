#include "enemy.h"
#include <SFML\Graphics.hpp>
#include <iostream>

enemy::enemy(double _hp, float _speed)
: HP(_hp), speed(_speed)
{
	if (!pTexture.loadFromFile("Images/enemy_1.png"))
		std::cout << "Error could not load enemy image." << std::endl;

	Image.setTexture(pTexture);

	std::cout << "Enemy created" << std::endl;

	Image.setPosition(sf::Vector2f(100, 100));

	source = sf::Vector2u(1, Down);
}

void enemy::HP_minus(double damaged)
{
	HP -= damaged;
}

double enemy::HP_left()
{
	return HP;
}

void enemy::nextAnimation()
{
	source.x++;

	// Reset Clock
	animationClock.restart();
}

void enemy::draw(sf::RenderWindow* Window, sf::Vector2f playerPosition)
{
	if (moveClock.getElapsedTime().asMilliseconds() > 10)
		enemy::move(playerPosition);

	if (animationClock.getElapsedTime().asMilliseconds() > (400 / speed))
		enemy::nextAnimation();

	if (source.x * 32 >= pTexture.getSize().x)
		source.x = 0;

	Image.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));

	Window->draw(Image);
}

void enemy::move(sf::Vector2f playerPosition)
{
	// Enemy movement

	if (playerPosition.x > Image.getPosition().x)
	{
		Image.move(speed, 0);
	}
	else if (playerPosition.x < Image.getPosition().x)
	{
		Image.move(-speed, 0);
	}

	if (playerPosition.y > Image.getPosition().y)
	{
		Image.move(0, speed);
		source.y = Down;
	}
	else if (playerPosition.y < Image.getPosition().y)
	{
		Image.move(0, -speed);
		source.y = Up;
	}

	/*if ((playerPosition.x - Image.getPosition().x) > (playerPosition.y - Image.getPosition().y))
		source.y = Up;
	else if ((playerPosition.x - Image.getPosition().x) < (playerPosition.y - Image.getPosition().y))
		source.y = Down;*/

	// Reset Clock
	moveClock.restart();
}