#ifndef __MENUSCREEN_H_INCLUDED__
#define __MENUSCREEN_H_INCLUDED__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "cScreen.h"
#include "VideoSettings.h"

class MenuScreen : public cScreen
{
private:
	// Settings
	VideoSettings *videoSettings;

	// Buttons
	sf::Text storyButton;
	sf::Text multiplayerButton;
	sf::Text settingsButton;
	sf::Text exitButton;

	enum menuButton { STORY, MULTIPLAYER, SETTINGS, EXIT };
	
	// Background
	sf::Texture Texture;
	sf::Sprite Sprite;

	sf::Event Event;
	bool Running = true;
	sf::Font Font;
	int numberOfButtons = 4;
	int menu = STORY;
public:
	MenuScreen(VideoSettings *videoSettings);
	virtual int Run(sf::RenderWindow &App);
};

#endif // !__MENUSCREEN_H_INCLUDED__