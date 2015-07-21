#ifndef __LANMENUSCREEN_H_INCLUDED__
#define __LANMENUSCREEN_H_INCLUDED__

#include <iostream>
#include "cScreen.h"
#include "VideoSettings.h"
#include "MenuManager.h"
#include "MenuScreen.h"
#include "Screens.h"
#include <SFML\Network.hpp>

class LanMenuScreen : public cScreen, public MenuScreen
{
private:
	// Buttons
	Button createButton;
	Button joinButton;
	Button backButton;

	void setButtonsSelected(int selectedButton);
	void draw(sf::RenderWindow &App);

	enum lanButton { CREATE, JOIN, BACK };

	int numberOfButtons = 3;
	int selectedButton = CREATE;
public:
	LanMenuScreen(VideoSettings *videoSettings);
	~LanMenuScreen();
	virtual int Run(sf::RenderWindow &App);
};

#endif // !__LANMENUSCREEN_H_INCLUDED__