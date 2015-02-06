#include <SFML/Graphics.hpp>

class armor
{
public:
	armor(double armor_hp = 50);
	~armor();
	sf::Time time_left();
	double armor_left();
	sf::Sprite armorImage;

private:
	double hp;
	sf::Clock time;
	sf::Texture pTexture;
};