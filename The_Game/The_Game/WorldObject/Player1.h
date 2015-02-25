#include "Character.h"

class Player : public Character
{
public:
	Player(int HP = 100, float moveSpeed = 1);
	~Player();
	void changeState(sf::RenderWindow *Window);
	// GET

private:
	// Sounds
	sf::SoundBuffer walkBuffer, sprintBuffer;
	sf::Sound walkSound, sprintSound;

	void move();

	// Keys - meneni klaves pomoci eventu

	sf::Keyboard::Key sprintKey = sf::Keyboard::LShift;
	sf::Keyboard::Key upKey = sf::Keyboard::Up;
	sf::Keyboard::Key downKey = sf::Keyboard::Down;
	sf::Keyboard::Key leftKey = sf::Keyboard::Left;
	sf::Keyboard::Key rightKey = sf::Keyboard::Right;
	sf::Keyboard::Key fireKey = sf::Keyboard::LControl;

	// Text

	sf::Font gameFont;
	sf::String string;
	sf::Text text;
};