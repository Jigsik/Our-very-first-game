#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>

// ARMOR INCLUDE GUARD
#ifndef __ARMOR_H_INCLUDED__
#define __ARMOR_H_INCLUDED__
#include "Armor.h"
#endif

class player
{
	public:
		player(double HP = 100, float speed = 1);
		~player();
		void recieveDamage(int damaged = 20);
		void draw(sf::RenderWindow* Window);
		void shoot();

		// GET

		sf::Vector2i getDirection();
		sf::Vector2f getPosition();
		sf::Vector2u getCharacterSize();
		/**
		 Gets player hitpoints
		 <returns>The player hit points</returns>
		 */
		double getHP();

		// ACTIVATE

		
		void activateArmor();

	private:
		// It means - Down = 0, Left = 1, Right = 2, Up = 3
		enum Direction { Down, Left, Right, Up };

		int HP;
		float speed;

		sf::Sprite playerImage;
		sf::Vector2u source, characterSize;
		sf::Vector2i direction;
		sf::Texture pTexture;
		sf::Clock moveClock, animationClock;

		sf::Font HPFont;
		sf::Text HPText;

		armor *brneni = 0;

		// Private Methods
		void move();
		void nextAnimation();

		// Sounds
		sf::SoundBuffer walkBuffer, sprintBuffer;
		sf::Sound walk, sprintSound;
};