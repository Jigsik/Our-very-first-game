#include <SFML\Graphics.hpp>

class armor
{
public:
	armor(double armor_hp = 50);
	~armor();

	// GET
	sf::Time getTime();
	double getHP();

	// Public methods
	void draw(sf::RenderWindow* Window, sf::Vector2f playerPosition);

private:
	double hp;
	sf::Clock time;
	sf::Clock rotateClock;
	sf::Texture pTexture;
	sf::Sprite armorImage;
	sf::Sprite armorImage1;
};