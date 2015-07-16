#ifndef __SETTINGSSCREEN_H_INCLUDED__
#define __SETTINGSSCREEN_H_INCLUDED__

#include <iostream>
#include "cScreen.h"
#include "VideoSettings.h"

class SettingsScreen : public cScreen
{
public:
	SettingsScreen(VideoSettings *videoSettings);
	~SettingsScreen();
	virtual int Run(sf::RenderWindow &App);
private:
	// Settings
	VideoSettings *videoSettings;

	// Background
	sf::Texture Texture;
	sf::Sprite Sprite;

	sf::Event Event;
	sf::Font Font;

	sf::Text resolutionLabel;
	sf::Text ratioLabel;

	sf::Text res1, res2;
	sf::Text ratio1;

	sf::Text applyLabel;
	sf::Text cancelLabel;
};

#endif // !__SETTINGSSCREEN_H_INCLUDED__