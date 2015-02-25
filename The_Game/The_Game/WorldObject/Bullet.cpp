#include "Bullet.h"

Bullet::Bullet(sf::Vector2f characterPosition, sf::Vector2i direction, sf::Vector2u characterSize)
{
	// Texture

	if (!pTexture.loadFromFile("Images/bullet.png"))
		std::cout << "Error could not load bullet image." << std::endl;

	image.setTexture(pTexture);

	speed = 2;

	// Position

	image.setOrigin(sf::Vector2f(0, (float)(pTexture.getSize().y / 2)));

	image.setPosition(characterPosition.x + (characterSize.x / 2), characterPosition.y + (characterSize.x / 2));

	image.setOrigin(sf::Vector2f((float)pTexture.getSize().x / 2, (float)(pTexture.getSize().y / 2)));

	// Direction

	this->direction = direction;

	if (direction.x == 1 && direction.y == 0)
	{
		image.setRotation(180);
	}
	else if (direction.x == -1 && direction.y == 0)
	{
		image.setRotation(0);
	}
	else if (direction.x == 0 && direction.y == 1)
	{
		image.setRotation(270);
	}
	else if (direction.x == 0 && direction.y == -1)
	{
		image.setRotation(90);
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

	std::cout << "Bullet Launched" << std::endl;
}

void Bullet::changeState(sf::RenderWindow *Window)
{
	if (moveClock.getElapsedTime().asMilliseconds() > 10)
		move();

	if (animationClock.getElapsedTime().asMilliseconds() > 150)
		nextAnimation();

	if (source.x * getSize().x >= pTexture.getSize().x)
		source.x = 0;

	image.setTextureRect(sf::IntRect(source.x * getSize().x, 0, getSize().x / 2, getSize().y));
}

void Bullet::move()
{
	// Enemy movement

	//speed *= (float) 1.015;

	if (direction.x == 0 || direction.y == 0)
	{
		image.move(direction.x * speed, direction.y * speed);
	}
	else {
		float pom = sqrt((speed*speed) / 2);
		image.move(direction.x * pom, direction.y * pom);
	}

	// Reset Clock
	moveClock.restart();
}

Bullet::~Bullet()
{
}