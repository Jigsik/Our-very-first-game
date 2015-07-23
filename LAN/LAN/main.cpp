#include <iostream>
#include <SFML/Graphics.hpp>
#include "VideoSettings.h"

// Menu
#include "MainMenu.h"
#include "Multiplayer.h"

int main(int argc, char** argv)
{
	// Video Settings
	VideoSettings *videoSettings = new VideoSettings();

	// Applications variables
	std::vector<MenuScreen*> Screens;
	int activeScreen = 0;

	// Window creation
	sf::RenderWindow App(
		sf::VideoMode(
			videoSettings->getScreenDimensions().x,
			videoSettings->getScreenDimensions().y),
		"THE GAME",
		sf::Style::Close);

	// Mouse cursor no more visible
	App.setMouseCursorVisible(false);

	// Screens preparations
	MainMenu mainMenuScreen(videoSettings);
	Screens.push_back(&mainMenuScreen);
	Multiplayer multiPlayerScreen(videoSettings);
	Screens.push_back(&multiPlayerScreen);

	while (activeScreen >= 0)
	{
		std::cout << "Running screen " << activeScreen << std::endl;
		activeScreen = Screens[activeScreen]->Run(App);
	}

	delete videoSettings;

	return EXIT_SUCCESS;
}