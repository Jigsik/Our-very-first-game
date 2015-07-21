#include <iostream>
#include <SFML/Graphics.hpp>
#include "Screens.h"
#include "VideoSettings.h"

int main(int argc, char** argv)
{
	enum ScreenNames { MAIN, MULTIPLAYER, SETTINGS, LAN, LANCREATE, LANJOIN };

	// Video Settings
	VideoSettings *videoSettings = new VideoSettings();

	// Applications variables
	std::vector<cScreen*> Screens;
	int screen = MAIN;

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
	MainMenu menuScreen(videoSettings);
	Screens.push_back(&menuScreen);
	MultiplayerScreen multiplayerScreen(videoSettings);
	Screens.push_back(&multiplayerScreen);
	SettingsScreen settingsScreen(videoSettings);
	Screens.push_back(&settingsScreen);
	LanMenuScreen lanMenuScreen(videoSettings);
	Screens.push_back(&lanMenuScreen);
	LanCreate lanCreateScreen(videoSettings);
	//LanCreate *lanCreateScreen = NULL;
	Screens.push_back(&lanCreateScreen);
	LanJoin lanJoinScreen(videoSettings);
	Screens.push_back(&lanJoinScreen);
	//GameScreen s1(App, settings);
	//Screens.push_back(&s1);

	/*
	Menu		0
	Multiplayer	1
	Settings	2
	LAN			3
	LAN Create	4
	LAn Join	5
	*/

	//Main loop
	bool lanCreated = false;

	while (screen >= 0)
	{
		/*if (screen == LANCREATE)
		{
			Screens[screen] = new LanCreate(videoSettings);
			//lanCreateScreen = new LanCreate(videoSettings);
			lanCreated = true;

			//std::cout << lanCreateScreen << std::endl;
		}*/

		std::cout << "Running screen " << screen << std::endl;
		screen = Screens[screen]->Run(App);

		/*if (lanCreated)
		{
			delete Screens[LANCREATE];
			lanCreated = false;
		}*/
	}

	delete videoSettings;

	return EXIT_SUCCESS;
}