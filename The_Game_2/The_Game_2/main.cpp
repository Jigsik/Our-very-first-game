#include <iostream>
#include <SFML/Graphics.hpp>
#include "Screens.h"
#include "VideoSettings.h"

int main(int argc, char** argv)
{
	// Video Settings
	VideoSettings *videoSettings = new VideoSettings();

	// Applications variables
	std::vector<cScreen*> Screens;
	int screen = 0;

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
	MenuScreen menuScreen(videoSettings);
	Screens.push_back(&menuScreen);
	MultiplayerScreen multiplayerScreen(videoSettings);
	Screens.push_back(&multiplayerScreen);
	SettingsScreen settingsScreen(videoSettings);
	Screens.push_back(&settingsScreen);
	Screens.push_back(&settingsScreen);
	LanMenuScreen lanMenuScreen(videoSettings);
	Screens.push_back(&lanMenuScreen);
	LanCreate lanCreateScreen(videoSettings);
	Screens.push_back(&lanCreateScreen);
	//GameScreen s1(App, settings);
	//Screens.push_back(&s1);

	/*
	Menu		0
	Multiplayer	1
	Settings	2
	Splitscreen 3
	LAN			4
	Exit		5
	*/

	//Main loop
	while (screen >= 0)
	{
		std::cout << "Running screen " << screen << std::endl;
		screen = Screens[screen]->Run(App);
	}

	delete videoSettings;

	return EXIT_SUCCESS;
}