#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Player1.h"
#include "Rune.h"

class Game
{
public:
	Game(); // OK
	~Game();
	void play();

private:
	void setUpFont(); // OK
	void setUpSound();
	void countFPS();
	void handlingRunes();

	bool isPause = false;

protected:
	// Texts
	sf::Font gameFont; // OK
	sf::String fpsString; // OK
	sf::Text fpsText; // OK
	sf::Event gameEvent; // OK
	int fps = 0; // OK

	// Window
	sf::RenderWindow Window; // OK

	// Clocks
	sf::Clock fpsClock, enemiesClock, rocketsClock, armorClock, runeClock; // OK

	// Sound
	sf::Music gameMusic;

	// Objects
	Player player;
	Rune *rune = 0;
};