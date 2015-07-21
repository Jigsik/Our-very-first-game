#ifndef __CSCREEN_H_INCLUDED__
#define __CSCREEN_H_INCLUDED__

#include <SFML/Graphics.hpp>

class cScreen
{
public:
	enum ScreenNames { X_MAIN, X_MULTIPLAYER, X_SETTINGS, X_LAN, X_LANCREATE, X_LANJOIN };
	virtual int Run(sf::RenderWindow &App) = 0;
};

#endif // !__CSCREEN_H_INCLUDED_