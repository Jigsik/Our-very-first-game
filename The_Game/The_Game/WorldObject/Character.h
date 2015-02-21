#include "WorldObject.h"

class Character : public WorldObject
{
public:
	Character(int _hp, float _moveSpeed);
	~Character();
	void receiveDamage(int damage);
	void activateArmor();

	// GET

	int getHP();
	sf::Vector2i getDirection();

private:
	
protected:
	sf::Clock moveClock, animationClock;
	float moveSpeed, speed;
	enum Direction { Down, Left, Right, Up };
	int HP;
	sf::Vector2u source = sf::Vector2u(0, Down);
	sf::Vector2i direction = sf::Vector2i(0, 1);
	// Armor *brneni = 0;
	void nextAnimation();

};