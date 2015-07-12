#include "WorldObject.h"

#ifndef __RUNE_H_INCLUDED__
#define __RUNE_H_INCLUDED__

class Rune : public WorldObject
{
public:
	//Rune();
	Rune(/*sf::Vector2u mapSize*/);
	~Rune();
	sf::Clock runeClock;
	int getType();
	int getDuration();
	

protected:
	enum Types {armorRune, speedRune};
	int numberOfRunes = 2;
	int type;
	int duration = 5;
	void setRune(std::string location, sf::Vector2u mapSize);
};

#endif // !__RUNE_H_INCLUDED__