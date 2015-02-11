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

	float x = playerPosition.x;
	float y = playerPosition.y;

	float xe = abs( playerPosition.x - Image.getPosition().x );
	float ye = abs( playerPosition.y - Image.getPosition().y );

	float pom = (sqrt(xe * xe + ye * ye) / speed);

	if ((playerPosition.x - Image.getPosition().x) > 1 && (playerPosition.y - Image.getPosition().y) > 1)
	{
		Image.move(xe / pom, ye / pom);
		//source.y = Left;
	}
	else if ((playerPosition.x - Image.getPosition().x) > 1 && (Image.getPosition().y - playerPosition.y) > 1)
	{
		Image.move((xe / pom), -(ye / pom));
		//source.y = Left;
	}
	else if ((Image.getPosition().x - playerPosition.x) > 1 && (playerPosition.y - Image.getPosition().y) > 1)
	{
		Image.move(-(xe / pom), ye / pom);
		//source.y = Left;
	}
	else if ((Image.getPosition().x - playerPosition.x) > 1 && (Image.getPosition().y - playerPosition.y) > 1)
	{
		Image.move(-(xe / pom), -(ye / pom));
		//source.y = Left;
	}
	else if ((playerPosition.x - Image.getPosition().x) > 1)
	{
		Image.move(speed, 0);
		source.y = Right;
	}
	else if ((Image.getPosition().x - playerPosition.x) > 1)
	{
		Image.move(-speed, 0);
		source.y = Left;
	}

	else if ((playerPosition.y - Image.getPosition().y) > 1)
	{
		Image.move(0, speed);
		source.y = Down;
	}
	else if ((Image.getPosition().y - playerPosition.y) > 1)
	{
		Image.move(0, -speed);
		source.y = Up;
	}

	//std::cout << Image.getPosition().x << " " << Image.getPosition().y << std::endl;

	/*if ((playerPosition.x - Image.getPosition().x) > (playerPosition.y - Image.getPosition().y))
		source.y = Up;
	else if ((playerPosition.x - Image.getPosition().x) < (playerPosition.y - Image.getPosition().y))
		source.y = Down;*/

	// Reset Clock
	moveClock.restart();
}