#include "WorldObject.h"

class Character : public WorldObject
{
public:
	/*Character();
	~Character();*/
	void receiveDamage(float damage);
	void activateArmor();

	// GET

	int getHP();
	sf::Vector2i getDirection();
	int HP;
	float speed;

private:
	enum Direction { Down, Left, Right, Up};
	sf::Clock moveClock, animationClock;
	
	sf::Vector2u source;
	
	sf::Vector2i direction;
	// Armor *brneni = 0;

protected:
	
};

/*Character::Character()
{
}

Character::~Character()
{
}*/