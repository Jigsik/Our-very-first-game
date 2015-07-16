#ifndef __MULTIPLAYERSCREEN_H_INCLUDED__
#define __MULTIPLAYERSCREEN_H_INCLUDED__

#include <iostream>
#include "cScreen.h"
#include "VideoSettings.h"

class MultiplayerScreen : public cScreen
{
private:
	// Settings
	VideoSettings *videoSettings;

	// Buttons
	sf::Text splitScreenButton;
	sf::Text lanButton;
	sf::Text backButton;

	enum multiplayerButton { SPLITSCREEN, LAN, BACK };

	// Background
	sf::Texture Texture;
	sf::Sprite Sprite;

	sf::Event Event;
	sf::Font Font;
	int numberOfButtons = 3;
	int selectedButton = SPLITSCREEN;
public:
	MultiplayerScreen(VideoSettings *videoSettings);
	~MultiplayerScreen();
	virtual int Run(sf::RenderWindow &App);
};

#endif // !__MULTIPLAYERSCREEN_H_INCLUDED__