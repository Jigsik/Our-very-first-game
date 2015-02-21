#include "Character.h"

Character::Character(int _hp, float _speed)
: HP(_hp), speed(_speed)
{
	std::cout << "Characted Created" << std::endl;
}

Character::~Character()
{
	std::cout << "Characted Destroyed" << std::endl;
}

void Character::receiveDamage(int damage)
{
	HP -= damage;
}

void Character::activateArmor()
{
}

int Character::getHP()
{
	return HP;
}

sf::Vector2i Character::getDirection()
{
	return direction;
}

void Character::nextAnimation()
{
	source.x++;
	animationClock.restart();
}