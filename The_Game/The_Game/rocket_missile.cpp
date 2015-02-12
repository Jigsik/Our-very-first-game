#include "rocket_missiles.h"
#include <SFML\Graphics.hpp>
#include <iostream>

rocket_missile::rocket_missile(sf::Vector2f playerPosition, sf::Vector2i rocket_direction)
{
	if (!pTexture.loadFromFile("Images/rocket_missile.gif"))
		std::cout << "Error could not load rocket missile image." << std::endl;

	image.setTexture(pTexture);
	image.setPosition(playerPosition);

	this->rocket_direction = rocket_direction;

	std::cout << "Missile launched" << std::endl;
}

void rocket_missile::draw(sf::RenderWindow* Window, sf::Vector2f enemyPosition)
{
	if (moveClock.getElapsedTime().asMilliseconds() > 10)
		rocket_missile::move(enemyPosition);

	image.setTextureRect(sf::IntRect(32, 32, 32, 32));

	Window->draw(image);
}

void rocket_missile::move(sf::Vector2f enemyPosition)
{
	// Enemy movement

	speed = 5;

	if (rocket_direction.x == 0 || rocket_direction.y == 0)
		image.move(rocket_direction.x * speed, rocket_direction.y * speed);
	else {
		float pom = sqrt((speed*speed)/2);
		image.move(rocket_direction.x * pom, rocket_direction.y * pom);
	}

	// Old move - it goes towards enemy - 100% kill - it can be used later

	/*if (enemyPosition.x > image.getPosition().x)
	{
		image.move(speed, 0);
	}
	else if (enemyPosition.x < image.getPosition().x)
	{
		image.move(-speed, 0);
	}

	if (enemyPosition.y > image.getPosition().y)
	{
		image.move(0, speed);
	}
	else if (enemyPosition.y < image.getPosition().y)
	{
		image.move(0, -speed);
	}*/

	// Reset Clock
	moveClock.restart();
}

rocket_missile::~rocket_missile()
{
}