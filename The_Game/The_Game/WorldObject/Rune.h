#include "WorldObject.h"

class Rune : public WorldObject
{
public:
	Rune();
	~Rune();
	sf::Clock runeClock;

private:
	enum Types {armorRune, speedRune};
	int numberOfRunes = 1;
};