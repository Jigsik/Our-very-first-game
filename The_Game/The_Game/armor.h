#include <SFML/Graphics.hpp>

class armor
{
public:
	armor(double armor_hp = 50);
	~armor();
	sf::Time time_left();
	double armor_left();
	void draw(sf::RenderWindow* Window);
	sf::Sprite armorImage;
	sf::Sprite armorImage1;

private:
	double hp;
	sf::Clock time;
	sf::Texture pTexture;
	sf::Texture pTexture1;
};