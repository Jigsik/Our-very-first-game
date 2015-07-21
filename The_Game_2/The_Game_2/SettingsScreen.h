#ifndef __SETTINGSSCREEN_H_INCLUDED__
#define __SETTINGSSCREEN_H_INCLUDED__

#include <iostream>
#include "cScreen.h"
#include "VideoSettings.h"
#include "MenuManager.h"
#include "MenuScreen.h"

class SettingsScreen : public cScreen, public MenuScreen
{
public:
	SettingsScreen(VideoSettings *videoSettings);
	~SettingsScreen();
	virtual int Run(sf::RenderWindow &App);
private:
	sf::Text resolutionLabel;
	sf::Text ratioLabel;

	sf::Text res1, res2;
	sf::Text ratio1;

	sf::Text applyLabel;
	sf::Text cancelLabel;

	void draw(sf::RenderWindow &App);
};

#endif // !__SETTINGSSCREEN_H_INCLUDED__