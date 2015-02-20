#include "Character.h"

class Player : Character
{
public:
	Player(int HP = 100, float speed = 1);
	~Player();

	// GET

private:
	// Sounds
	sf::SoundBuffer walkBuffer, sprintBuffer;
	sf::Sound walkSound, sprintSound;
};