#ifndef __MULTIPLAYERSCREEN_H_INCLUDED__
#define __MULTIPLAYERSCREEN_H_INCLUDED__

#include <iostream>
#include "VideoSettings.h"
#include "MenuManager.h"
#include "MenuScreen.h"

class Multiplayer : public MenuScreen
{
private:
	// Buttons
	Button splitScreenButton;
	Button lanButton;
	Button backButton;
	void selectButton();
	enum menuButton { B_SPLITSCREEN, B_LAN, B_BACK };
public:
	Multiplayer(VideoSettings *videoSettings);
	virtual int Run(sf::RenderWindow &App);
};

#endif // !__MULTIPLAYERSCREEN_H_INCLUDED__