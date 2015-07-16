#ifndef __LANMENUSCREEN_H_INCLUDED__
#define __LANMENUSCREEN_H_INCLUDED__

#include <iostream>
#include "cScreen.h"
#include "VideoSettings.h"
#include <SFML\Network.hpp>

class LanMenuScreen : public cScreen
{
private:
	// Settings
	VideoSettings *videoSettings;

	// Buttons
	sf::Text createButton;
	sf::Text joinButton;
	sf::Text backButton;

	enum lanButton { CREATE, JOIN, BACK };

	// Background
	sf::Texture Texture;
	sf::Sprite Sprite;

	sf::Event Event;
	sf::Font Font;
	int numberOfButtons = 3;
	int selectedButton = CREATE;
public:
	LanMenuScreen(VideoSettings *videoSettings);
	~LanMenuScreen();
	virtual int Run(sf::RenderWindow &App);
};

#endif // !__LANMENUSCREEN_H_INCLUDED__