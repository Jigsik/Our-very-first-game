#include <SFML/Graphics.hpp>

class armor
{
public:
	armor(double armor_hp = 50);
	~armor();
	sf::Time time_left();

private:
	double armor_hp;
	sf::Clock armor_time;
};