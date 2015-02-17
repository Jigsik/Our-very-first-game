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
		float speed;
		sf::Sprite playerImage;
		sf::Vector2i rocket_direction;

	private:
		// It means - Down = 0, Left = 1, Right = 2, Up = 3
		enum Direction { Down, Left, Right, Up };
		double HP;
		sf::Vector2u source;
		sf::Texture pTexture;
		sf::Clock moveClock;
		sf::Clock animationClock;

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