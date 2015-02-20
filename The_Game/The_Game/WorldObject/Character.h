#include "WorldObject.h"

class Character : public WorldObject
{
public:
	Character(int _hp, float _speed);
	~Character();
	void receiveDamage(int damage);
	void activateArmor();

	// GET

	int getHP();
	sf::Vector2i getDirection();

private:
	enum Direction { Down, Left, Right, Up};
	sf::Clock moveClock, animationClock;
	int HP;
	float speed;
	sf::Vector2u source;
	sf::Vector2i direction;
	// Armor *brneni = 0;
	void nextAnimation();

protected:
	
};