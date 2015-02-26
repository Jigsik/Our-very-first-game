#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include "Player1.h"
#include "Rune.h"
#include "Bullet.h"
#include "Map.h"

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
	void handlingViews();
	void draw();

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
	sf::Vector2u screenDimensions = sf::Vector2u(800, 500);
	sf::Vector2f position;

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
	sf::View player1_view;
	sf::View player2_view;
	sf::View barView1;
	sf::View barView2;

	// Map
	Map mapa;
};