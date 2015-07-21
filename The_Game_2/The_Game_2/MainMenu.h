#ifndef __MAINMENU_H_INCLUDED__
#define __MAINMENU_H_INCLUDED__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "cScreen.h"
#include "VideoSettings.h"
#include "MenuManager.h"
#include "MenuScreen.h"

class MainMenu : public cScreen, public MenuScreen
{
private:
	// Buttons
	Button storyButton;
	Button multiplayerButton;
	Button settingsButton;
	Button exitButton;

	void setButtonsSelected(int selectedButton);
	void draw(sf::RenderWindow &App);

	enum menuButton { STORY, MULTIPLAYER, SETTINGS, EXIT };

	bool Running = true;
	const int numberOfButtons = 4;
	int selectedButton = STORY;
public:
	MainMenu(VideoSettings *videoSettings);
	virtual int Run(sf::RenderWindow &App);
};

#endif // !__MAINMENU_H_INCLUDED__