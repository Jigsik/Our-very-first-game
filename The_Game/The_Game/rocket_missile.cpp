#include "rocket_missiles.h"
#include <SFML\Graphics.hpp>
#include <iostream>

rocket_missile::rocket_missile(sf::Vector2f playerPosition, sf::Vector2i rocket_direction)
{
	if (!pTexture.loadFromFile("Images/rocket_missile.png"))
		std::cout << "Error could not load rocket missile image." << std::endl;

	image.setTexture(pTexture);

	this->rocket_direction = rocket_direction;
	
	std::cout << "rocket_direction.x = " << rocket_direction.x << std::endl;
	std::cout << "rocket_direction.y = " << rocket_direction.y << std::endl;

	if (rocket_direction.x == 1 && rocket_direction.y == 0)
	{
		image.setPosition(playerPosition.x + 40, playerPosition.y + 20);
		image.setRotation(180);
	}
	else if (rocket_direction.x == -1 && rocket_direction.y == 0)
	{
		image.setPosition(playerPosition.x, playerPosition.y + 10);
		image.setRotation(0);
	}
	else if (rocket_direction.x == 0 && rocket_direction.y == 1)
	{
		image.setPosition(playerPosition.x + 12, playerPosition.y + 30);
		image.setRotation(270);
	}
	else if (rocket_direction.x == 0 && rocket_direction.y == -1)
	{
		image.setPosition(playerPosition.x + 20, playerPosition.y);
		image.setRotation(90);
	}
	else if (rocket_direction.x == 1 && rocket_direction.y == 1)
	{
		image.setPosition(playerPosition.x + 25, playerPosition.y + 25);
		image.setRotation(225);
	}
	else if (rocket_direction.x == 1 && rocket_direction.y == -1)
	{
		image.setPosition(playerPosition.x + 25, playerPosition.y + 10);
		image.setRotation(135);
	}
	else if (rocket_direction.x == -1 && rocket_direction.y == 1)
	{
		image.setPosition(playerPosition.x + 5, playerPosition.y + 25);
		image.setRotation(315);
	}
	else if (rocket_direction.x == -1 && rocket_direction.y == -1)
	{
		image.setPosition(playerPosition.x + 10, playerPosition.y + 10);
		image.setRotation(45);
	}
		

	std::cout << "Missile launched" << std::endl;
}

void rocket_missile::draw(sf::RenderWindow* Window, sf::Vector2f enemyPosition)
{
	if (moveClock.getElapsedTime().asMilliseconds() > 10)
		rocket_missile::move(enemyPosition);

	image.setTextureRect(sf::IntRect(0, 0, 25, 10));

	Window->draw(image);
}

void rocket_missile::move(sf::Vector2f enemyPosition)
{
	// Enemy movement

	speed = 5;

	if (rocket_direction.x == 0 || rocket_direction.y == 0)
	{
		image.move(rocket_direction.x * speed, rocket_direction.y * speed);
	}
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