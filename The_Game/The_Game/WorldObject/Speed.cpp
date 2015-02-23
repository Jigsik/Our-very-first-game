#include "Speed.h"

Speed::Speed()
{
}

Speed::~Speed()
{
}

void Speed::draw(sf::RenderWindow *Window)
{
	// text

	text.setPosition(sf::Vector2f((float)Window->getSize().x - 200, 0));

	string = std::to_string(10 - (int)clock.getElapsedTime().asSeconds());

	text.setString("Speed: " + string + "s");

	// KOnec TEXT

	Window->draw(text);
}