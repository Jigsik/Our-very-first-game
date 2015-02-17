#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Armor.h"
#include <iostream>

class player
{
	public:
		player(double HP = 100, float speed = 1);
		~player();
		void HP_minus(double damaged);
		double HP_left();
		void draw(sf::RenderWindow* Window);
		void activateArmor();
		void shoot();

		// GET
		sf::Vector2i getRocket_direction();
		sf::Vector2f getPosition();

	private:
		// It means - Down = 0, Left = 1, Right = 2, Up = 3
		enum Direction { Down, Left, Right, Up };
		double HP;
		sf::Sprite playerImage;
		sf::Vector2u source;
		sf::Texture pTexture;
		sf::Clock moveClock;
		sf::Clock animationClock;
		float speed;

		sf::Vector2i rocket_direction;

		armor *brneni = 0;

		// Private Methods
		void move();
		void nextAnimation();

		sf::Vector2u characterSize;

		// Sounds
		sf::SoundBuffer walkBuffer;
		sf::Sound walk;
		sf::SoundBuffer sprintBuffer;
		sf::Sound sprintSound;
};