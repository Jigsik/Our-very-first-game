#ifndef __MENUSCREEN_H_INCLUDED__
#define __MENUSCREEN_H_INCLUDED__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "VideoSettings.h"
#include "MenuManager.h"
#include "Button.h"

class MenuScreen
{
protected:
	// Settings
	VideoSettings *videoSettings;
	
	// Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundImage;

	sf::Event Event;
	sf::Font Font;
	unsigned fontSize;
public:
	void resolutionChanged();
	bool setFont();
	bool setBackground();
};

#endif // !__MENUSCREEN_H_INCLUDED__