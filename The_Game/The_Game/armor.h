#include <SFML\Graphics.hpp>
#include <iostream>

class armor
{
public:
	armor(double armor_hp = 50);
	~armor();

	// GET
	sf::Time getTime();
	double getHP();

	// Public methods
	void draw(sf::RenderWindow* Window, sf::Vector2f playerPosition, sf::Vector2u characterSize);

private:
	double hp;
	sf::Clock time;
	sf::Clock rotateClock;
	sf::Texture pTexture;
	sf::Sprite armorImage;
	sf::Sprite armorImage1;
};