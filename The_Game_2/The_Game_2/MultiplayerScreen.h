#ifndef __MULTIPLAYERSCREEN_H_INCLUDED__
#define __MULTIPLAYERSCREEN_H_INCLUDED__

#include <iostream>
#include "cScreen.h"
#include "VideoSettings.h"
#include "MenuManager.h"
#include "MenuScreen.h"

class MultiplayerScreen : public cScreen, public MenuScreen
{
private:
	// Buttons
	Button splitScreenButton;
	Button lanButton;
	Button backButton;

	// Functions
	void setButtonsSelected(int selectedButton);
	void draw(sf::RenderWindow &App);

	enum multiplayerButton { SPLITSCREEN, LAN, BACK };

	const int numberOfButtons = 3;
	int selectedButton = SPLITSCREEN;
public:
	MultiplayerScreen(VideoSettings *videoSettings);
	~MultiplayerScreen();
	virtual int Run(sf::RenderWindow &App);
};

#endif // !__MULTIPLAYERSCREEN_H_INCLUDED__