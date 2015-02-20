#include "Character.h"

class Player : Character
{
public:
	Player();
	~Player();

	// GET

	sf::Vector2i getDirection();

private:
	sf::Vector2i direction;

	// Sounds
	sf::SoundBuffer walkBuffer, sprintBuffer;
	sf::Sound walkSound, sprintSound;
};

Player::Player()
{
}

Player::~Player()
{
}