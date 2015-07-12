/*#include "WorldObject\Game.h"

int main()
{
	srand((unsigned)time(0));

	Game game;

	game.play();

	return 0;
}*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Screens.h"
#include "Settings.h"

int main(int argc, char** argv)
{
	// Settings
	Settings settings;

	//Applications variables
	std::vector<cScreen*> Screens;
	int screen = 0;

	//Window creation
	sf::RenderWindow App(sf::VideoMode(640, 480, 32), "SFML Demo 3");

	//Mouse cursor no more visible
	App.setMouseCursorVisible(false);

	//Screens preparations
	MenuScreen s0;
	Screens.push_back(&s0);
	GameScreen s1(App, settings);
	Screens.push_back(&s1);

	//Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}

	return EXIT_SUCCESS;
}