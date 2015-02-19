#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class rocket_missile
{
public:
	rocket_missile(sf::Vector2f playerPosition, sf::Vector2i direction, sf::Vector2u characterSize);
	~rocket_missile();
	void draw(sf::RenderWindow* Window);
	sf::Vector2u getSize();
	sf::Vector2f getPosition();
	float getRotation();

private:
	float speed;
	sf::Texture pTexture;
	sf::Sprite image;
	sf::Clock moveClock;
	sf::Clock animationClock;
	sf::Vector2u source;
	sf::Vector2i direction;
	sf::Vector2u size;
	sf::Vector2u numberOfAnimations = sf::Vector2u(2, 1);

	void move();
	void nextAnimation();

	sf::SoundBuffer rocketBuffer;
	sf::Sound rocketSound;
};