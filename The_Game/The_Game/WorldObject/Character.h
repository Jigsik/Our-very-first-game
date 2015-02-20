#include "WorldObject.h"

class Character : public WorldObject
{
public:
	Character();
	~Character();
	void receiveDamage(float damage);
	void activateArmor();

	// GET

	int getHP();

private:
	enum Direction { Down, Left, Right, Up};
	sf::Clock moveClock, animationClock;
	float speed;
	sf::Vector2u source;
	int HP;
	// Armor *brneni = 0;

protected:
};

Character::Character()
{
}

Character::~Character()
{
}