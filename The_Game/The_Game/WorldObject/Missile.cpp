#include "Missile.h"

Missile::Missile()
{
	std::cout << "Missile created" << std::endl;
}

Missile::~Missile()
{
}

void Missile::nextAnimation()
{
	// Go to next animation
	source.x++;

	// Reset Clock
	animationClock.restart();
}