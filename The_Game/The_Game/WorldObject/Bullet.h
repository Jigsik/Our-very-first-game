#include "Missile.h"

class Bullet : public Missile
{
public:
	Bullet(sf::Vector2f characterPosition, sf::Vector2i direction, sf::Vector2u characterSize);
	~Bullet();
	void draw(sf::RenderWindow *Window);

private:
	void move();
};