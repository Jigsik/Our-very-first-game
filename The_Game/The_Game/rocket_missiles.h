#include <SFML\Graphics.hpp>

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
	float x;
	float y;
	sf::Vector2i rocket_direction;

	void move(sf::Vector2f enemyPosition);
};