#include "WorldObject\ArmorRune.h"
#include "WorldObject\SpeedRune.h"

class RuneFactory
{
public:
	static Rune* createRune(int type, sf::Vector2u mapSize);

private:
	enum Types { armorRune, speedRune };
};