#ifndef __CSCREEN_H_INCLUDED__
#define __CSCREEN_H_INCLUDED__

#include <SFML/Graphics.hpp>

class cScreen
{
public:
	virtual int Run(sf::RenderWindow &App) = 0;
};

#endif // !__CSCREEN_H_INCLUDED_