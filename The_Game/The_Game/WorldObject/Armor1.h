#include "Buff.h"

#ifndef __ARMOR_H_INCLUDED__
#define __ARMOR_H_INCLUDED__

class Armor : public Buff
{
public:
	Armor();
	~Armor();
	void draw(sf::RenderWindow *Window, sf::Vector2f playerPosition, sf::Vector2u characterSize);
	int getHP();

private:
	sf::Sprite image1;
	sf::Clock rotateClock;
	int HP = 100;
};

#endif // !__ARMOR_H_INCLUDED__