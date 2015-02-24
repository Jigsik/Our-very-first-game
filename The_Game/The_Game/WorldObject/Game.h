#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "Player1.h"
#include "Rune.h"
#include "Bullet.h"

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
	void collisions();
	void handlingBuffs();
	void handlingMissiles();
	void hanglingCharacters();
	void loadMap();

	bool isPause = false;

protected:
	enum Types { armorRune, speedRune };

	// Texts
	sf::Font gameFont; // OK
	sf::String fpsString; // OK
	sf::Text fpsText; // OK
	sf::Event gameEvent; // OK
	int fps = 0; // OK

	// Window
	sf::RenderWindow *Window = 0; // OK

	// Clocks
	sf::Clock fpsClock, enemiesClock, rocketsClock, armorClock,
			  runeClock, bulletsClock; // OK

	// Sound
	sf::Music gameMusic;

	// Objects
	Player player;
	Rune *rune = 0;

	// Missiles
	std::vector<Bullet*> bullets;

	// Iterators
	std::vector<Bullet*>::iterator bulletsIt;

	// Views
	sf::View view1;

	// Map
	sf::Texture tileTexture;
	sf::Sprite tiles;
	int map[100][100];
	sf::Vector2i mapSize;
};