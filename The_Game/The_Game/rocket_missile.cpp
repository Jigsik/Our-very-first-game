#include "rocket_missiles.h"
#include <SFML\Graphics.hpp>
#include <iostream>

rocket_missile::rocket_missile(sf::Vector2f playerPosition, sf::Vector2i direction, sf::Vector2u characterSize)
{
	// Texture

	if (!pTexture.loadFromFile("Images/rocket_missile.png"))
		std::cout << "Error could not load rocket missile image." << std::endl;

	image.setTexture(pTexture);

	// Sound

	if (!rocketBuffer.loadFromFile("Sounds/rocket_missile_sound.wav"))
		std::cout << "Error could not load rocket_missile sound." << std::endl;

	rocketSound.setBuffer(rocketBuffer);
	rocketSound.setVolume(40);
	rocketSound.play();

	speed = 2;

	this->direction = direction;

	image.setOrigin(sf::Vector2f(0, (float)(pTexture.getSize().y / 2)));

	image.setPosition(playerPosition.x + (characterSize.x / 2), playerPosition.y + (characterSize.x / 2));

	image.setOrigin(sf::Vector2f((float)pTexture.getSize().x / 2, (float)(pTexture.getSize().y / 2)));

	if (direction.x == 1 && direction.y == 0)
	{
		image.setRotation(180);
		//image.move(image.getOrigin().x, image.getOrigin().y);
	}
	else if (direction.x == -1 && direction.y == 0)
	{
		image.setRotation(0);
		//image.move(-image.getOrigin().x, -image.getOrigin().y);
	}
	else if (direction.x == 0 && direction.y == 1)
	{
		image.setRotation(270);
		//image.move(0, image.getOrigin().y);
	}
	else if (direction.x == 0 && direction.y == -1)
	{
		image.setRotation(90);
		//image.move(0, image.getOrigin().y);
	}
	else if (direction.x == 1 && direction.y == 1)
	{
		image.setRotation(225);
	}
	else if (direction.x == 1 && direction.y == -1)
	{
		image.setRotation(135);
	}
	else if (direction.x == -1 && direction.y == 1)
	{
		image.setRotation(315);
	}
	else if (direction.x == -1 && direction.y == -1)
	{
		image.setRotation(45);
	}

	size.x = pTexture.getSize().x / numberOfAnimations.x;
	size.y = pTexture.getSize().y / numberOfAnimations.y;

	//image.move(0, image.getOrigin().y);

	//image.setOrigin(sf::Vector2f(0,0));

	std::cout << "Missile launched" << std::endl;
}

void rocket_missile::draw(sf::RenderWindow* Window)
{
	if (moveClock.getElapsedTime().asMilliseconds() > 10)
		rocket_missile::move();

	if (animationClock.getElapsedTime().asMilliseconds() > 150)
		rocket_missile::nextAnimation();

	if (source.x * 40 >= pTexture.getSize().x)
		source.x = 0;

	image.setTextureRect(sf::IntRect(source.x * (pTexture.getSize().x / 2), 0, (pTexture.getSize().x / 2), (pTexture.getSize().y)));

	Window->draw(image);
}

void rocket_missile::nextAnimation()
{
	// Go to next animation
	source.x++;

	// Reset Clock
	animationClock.restart();
}

sf::Vector2f rocket_missile::getPosition()
{
	return image.getPosition();
}

sf::Vector2u rocket_missile::getSize()
{
	return sf::Vector2u(size);
}

float rocket_missile::getRotation()
{
	return image.getRotation();
}

void rocket_missile::move()
{
	// Enemy movement

	speed *= (float) 1.015;

	if (direction.x == 0 || direction.y == 0)
	{
		image.move(direction.x * speed, direction.y * speed);
	}
	else {
		float pom = sqrt((speed*speed)/2);
		image.move(direction.x * pom, direction.y * pom);
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
	rocketSound.stop();
}