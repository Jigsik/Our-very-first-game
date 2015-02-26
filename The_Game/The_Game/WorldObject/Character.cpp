#include "Character.h"

Character::Character(int _hp, float _speed)
: HP(_hp), speed(_speed)
{
	std::cout << "Characted Created" << std::endl;
}

Character::~Character()
{
	if (armor)
		delete armor;
	else if (speedBuff)
		delete speedBuff;

	std::cout << "Characted Destroyed" << std::endl;
}

void Character::receiveDamage(int damage)
{
	HP -= damage;
}

void Character::activateArmor()
{
	if (speedBuff)
	{
		moveSpeed /= speedBuff->speed;
		delete speedBuff;
		speedBuff = 0;
	}

	if (!armor)
	{
		armor = new Armor;
	}
	else
	{
		delete armor;
		armor = new Armor;
	}
}

void Character::drawBuffs(sf::RenderWindow *Window, sf::View view1, sf::View view2, sf::View barView1, sf::View barView2)
{
	if (armor)
	{
		if (armor->clock.getElapsedTime().asSeconds() > 10)
		{
			delete armor;
			armor = 0;
		}
		else
		{
			Window->setView(barView1);
			armor->changeState(Window, getPosition(), getSize());
			Window->setView(barView2);
			armor->changeState(Window, getPosition(), getSize());

			Window->setView(view1);
			Window->draw(armor->image);
			Window->draw(armor->image1);

			Window->setView(view2);
			Window->draw(armor->image);
			Window->draw(armor->image1);
		}
	}
	else if (speedBuff)
	{
		if (speedBuff->clock.getElapsedTime().asSeconds() > 10)
		{
			moveSpeed /= speedBuff->speed;
			delete speedBuff;
			speedBuff = 0;
		}
		else
		{
			Window->setView(barView1);
			speedBuff->draw(Window);
			Window->setView(barView2);
			speedBuff->draw(Window);
		}
	}
}

void Character::activateSpeed()
{
	if (armor)
	{
		delete armor;
		armor = 0;
	}

	if (!speedBuff)
	{
		speedBuff = new Speed;
		moveSpeed *= speedBuff->speed;
	}
	else
	{
		delete speedBuff;
		speedBuff = new Speed;
	}

	std::cout << "Speed activated !" << std::endl;
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