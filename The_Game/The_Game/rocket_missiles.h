#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class rocket_missile
{
public:
	rocket_missile(sf::Vector2f playerPosition, sf::Vector2i rocket_direction);
	~rocket_missile();
	void draw(sf::RenderWindow* Window, sf::Vector2f playerPosition);

private:
	float speed;
	sf::Texture pTexture;
	sf::Sprite image;
	sf::Clock moveClock;
	sf::Clock animationClock;
	sf::Vector2u source;
	sf::Vector2i rocket_direction;

	void move(sf::Vector2f enemyPosition);
	void nextAnimation();

	sf::SoundBuffer rocketBuffer;
	sf::Sound rocketSound;
};