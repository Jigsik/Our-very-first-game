#include "WorldObject.h"

class Rune : public WorldObject
{
public:
	Rune(sf::Vector2u mapSize);
	~Rune();
	sf::Clock runeClock;
	int getType();
	int getDuration();
	

private:
	enum Types {armorRune, speedRune};
	int numberOfRunes = 2;
	int type;
	int duration = 5;
};