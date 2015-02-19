#include <iostream>
#include <SFML\Graphics.hpp>

class armor
{
public:
	armor(sf::Vector2u characterSize, double armor_hp = 50);
	~armor();

	sf::CircleShape kruh;
	sf::CircleShape kruh1;
	sf::CircleShape kruh2;

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
	float rotace = 0;
	sf::Clock kruhClock;
};