#include <SFML\Graphics.hpp>

class rocket_missile
{
public:
	rocket_missile(sf::Vector2f playerPosition);
	~rocket_missile();
	void draw(sf::RenderWindow* Window, sf::Vector2f playerPosition);

private:
	float speed;
	sf::Texture pTexture;
	sf::Sprite image;
	sf::Clock moveClock;

	void move(sf::Vector2f enemyPosition);
};