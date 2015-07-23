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
	enum ScreenNames { M_MAIN, M_MULTIPLAYER, M_LAN };

	// Settings
	VideoSettings *videoSettings;

	// Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundImage;

	// Font
	sf::Font Font;
	unsigned fontSize;

	// Buttons
	std::vector<Button*> buttons;
	std::vector<Button*>::iterator buttonsIt;
	int numberOfButtons;
	int selectedButton;

	sf::Event Event;
public:
	void resolutionChanged();
	bool setFont();
	bool setBackground();
	virtual int Run(sf::RenderWindow &App) = 0;

	// Buttons
	void setButtons();
	void draw(sf::RenderWindow &App);
	void setButtonsSelectedALL(bool selected);
};

#endif // !__MENUSCREEN_H_INCLUDED__