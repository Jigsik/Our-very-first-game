#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class player
{
	public:
		player(double HP = 100, float speed = 1);
		void HP_minus(double damaged);
		double HP_left();
		void draw(sf::RenderWindow* Window);
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
		void move();
		void nextAnimation();

		sf::SoundBuffer walkBuffer;
		sf::Sound walk;

		sf::SoundBuffer sprintBuffer;
		sf::Sound sprintSound;
};