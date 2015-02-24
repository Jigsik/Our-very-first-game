#include "WorldObject.h"

#ifndef __MISSILE_H_INCLUDED__
#define __MISSILE_H_INCLUDED__

class Missile : public WorldObject
{
public:
	Missile();
	~Missile();

private:

protected:
	void nextAnimation();
	float speed;
	sf::Vector2i direction;
	sf::Vector2u source = sf::Vector2u(0, Down);
	sf::Clock animationClock, moveClock;
};

#endif // !__MISSILE_H_INCLUDED__