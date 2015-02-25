#include "Missile.h"

class Bullet : public Missile
{
public:
	Bullet(sf::Vector2f characterPosition, sf::Vector2i direction, sf::Vector2u characterSize);
	~Bullet();
	void changeState(sf::RenderWindow *Window);

private:
	void move();
};