#include <SFML\Graphics.hpp>
#include <iostream>

// ARMOR INCLUDE GUARD
#ifndef __ARMOR_H_INCLUDED__
#define __ARMOR_H_INCLUDED__
#include "Armor.h"
#endif

class enemy
{
public:
	enemy(double HP = 100, float speed = (float) 1);
	~enemy();
	void HP_minus(double damaged);
	double HP_left();
	void draw(sf::RenderWindow* Window, sf::Vector2f playerPosition);
	sf::Sprite Image;
	float speed;
	void activateArmor();
	sf::Vector2u getSize();
	sf::Vector2f getPosition();

private:
	// It means - Down = 0, Left = 1, Right = 2, Up = 3
	enum Direction { Down, Left, Right, Up };
	double HP;
	sf::Vector2u source;
	sf::Texture pTexture;
	sf::Clock moveClock;
	sf::Clock animationClock;
	void move(sf::Vector2f playerPosition);
	void nextAnimation();
	sf::Vector2u characterSize;

	armor *brneni = 0;
};