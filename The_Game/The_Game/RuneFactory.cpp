#include "RuneFactory.h"

Rune* RuneFactory::createRune(int type, sf::Vector2u mapSize)
{
	switch (type)
	{
	case armorRune:
		return new ArmorRune(mapSize);
		break;
	case speedRune:
		return new SpeedRune(mapSize);
		break;
	/*default:
		break;*/
	}
}