#include "WorldObject.h"

class Rune : public WorldObject
{
public:
	Rune();
	~Rune();
	sf::Clock runeClock;
	int getType();
	int getSpawnTime();
	int getDuration();
	

private:
	enum Types {armorRune, speedRune};
	int numberOfRunes = 1;
	int type;
	int spawnTime = 10;
	int duration = 5;
};