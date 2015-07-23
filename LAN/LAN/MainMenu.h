#ifndef __MAINMENU_H_INCLUDED__
#define __MAINMENU_H_INCLUDED__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "VideoSettings.h"
#include "MenuManager.h"
#include "MenuScreen.h"

class MainMenu : public MenuScreen
{
private:
	// Buttons
	Button storyButton;
	Button multiplayerButton;
	Button settingsButton;
	Button exitButton;
	void selectButton();
	enum menuButton { B_STORY, B_MULTIPLAYER, B_SETTINGS, B_EXIT };
public:
	MainMenu(VideoSettings *videoSettings);
	virtual int Run(sf::RenderWindow &App);
};

#endif // !__MAINMENU_H_INCLUDED__