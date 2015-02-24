#include "WorldObject.h"
#include "Armor1.h"
#include "Speed.h"

#ifndef __CHARACTER_H_INCLUDED__
#define __CHARACTER_H_INCLUDED__

class Character : public WorldObject
{
public:
	Character(int _hp, float _moveSpeed);
	~Character();
	void receiveDamage(int damage);
	void activateArmor();
	void activateSpeed();
	void drawBuffs(sf::RenderWindow *Window);

	// GET

	int getHP();
	sf::Vector2i getDirection();

private:
	
protected:
	sf::Clock moveClock, animationClock, buffClock;
	float moveSpeed, speed;
	int HP;
	sf::Vector2u source = sf::Vector2u(0, Down);
	sf::Vector2i direction = sf::Vector2i(0, 1);
	void nextAnimation();
	Armor *armor = 0;
	Speed *speedBuff = 0;

};

#endif // !__CHARACTER_H_INCLUDED__