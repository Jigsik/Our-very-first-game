#include "player.h"
#include <SFML\Graphics.hpp>
#include <iostream>

player::player(double _hp, double _speed)
: HP(_hp), speed(_speed)
{
	sf::Texture playerTexture;
	sf::Sprite playerImage;

	if (!playerTexture.loadFromFile("player_1.png"))
		std::cout << "Error could not load player image." << std::endl;

	playerImage.setTexture(playerTexture);
}

void player::HP_minus(double damaged)
{
	HP -= damaged;
}

double player::HP_left()
{
	return HP;
}

void draw_player(sf::Sprite playerImage, sf::RenderWindow Window, sf::Vector2i source1)
{
	playerImage.setTextureRect(sf::IntRect(source1.x * 32, source1.y * 32, 32, 32));

	Window.draw(playerImage);
}