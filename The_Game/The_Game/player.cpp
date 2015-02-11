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

	source = sf::Vector2u(1, Down);
}

void player::HP_minus(double damaged)
{
	HP -= damaged;
}

double player::HP_left()
{
	return HP;
}

void player::nextAnimation()
{
	source.x++;

	// Reset Clock
	animationClock.restart();
}

void player::draw(sf::RenderWindow* Window)
{
	if (moveClock.getElapsedTime().asMilliseconds() > 10
		&& playerImage.getPosition().x >= 0
		&& playerImage.getPosition().y >= 0
		&& playerImage.getPosition().x <= Window->getSize().x - 32
		&& playerImage.getPosition().y <= Window->getSize().y - 32)
		player::move();

	if (playerImage.getPosition().x < 0) playerImage.setPosition(playerImage.getPosition().x + 1, playerImage.getPosition().y);
	else if (playerImage.getPosition().y < 0) playerImage.setPosition(playerImage.getPosition().x, playerImage.getPosition().y + 1);
	else if (playerImage.getPosition().x > Window->getSize().x - 32) playerImage.setPosition(playerImage.getPosition().x - 1, playerImage.getPosition().y);
	else if (playerImage.getPosition().y > Window->getSize().y - 32) playerImage.setPosition(playerImage.getPosition().x, playerImage.getPosition().y - 1);

	if (animationClock.getElapsedTime().asMilliseconds() > (400 / speed))
		player::nextAnimation();

	if (source.x * 32 >= pTexture.getSize().x)
		source.x = 0;

	playerImage.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));

	Window->draw(playerImage);
}

void player::move()
{
	// Movement speed
	speed = 1,5;

	// Increasing movement speed

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		speed *= 2;
	}

	// Player movement

	float diag_speed = sqrt((speed*speed)/2);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerImage.move(-diag_speed, -diag_speed);
		source.y = Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerImage.move(diag_speed, -diag_speed);
		source.y = Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerImage.move(diag_speed, diag_speed);
		source.y = Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerImage.move(-diag_speed, diag_speed);
		source.y = Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerImage.move(0, -speed);
		source.y = Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		playerImage.move(0, speed);
		source.y = Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerImage.move(-speed, 0);
		source.y = Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerImage.move(speed, 0);
		source.y = Right;
	}

	// Reset Clock
	moveClock.restart();
}