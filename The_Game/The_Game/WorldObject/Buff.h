#include "WorldObject.h"

#ifndef __BUFF_H_INCLUDED__
#define __BUFF_H_INCLUDED__

class Buff : public WorldObject
{
public:
	Buff();
	~Buff();
	sf::Clock clock;

private:
	int duration = 5;

protected:
	// Text

	sf::Font gameFont;
	sf::String string;
	sf::Text text;
};

#endif // !__BUFF_H_INCLUDED__