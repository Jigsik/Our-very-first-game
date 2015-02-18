#include "Armor.h"

armor::armor(sf::Vector2u characterSize, double _armor_hp)
: hp(_armor_hp)
{
	kruh.setRadius(10);
	kruh.setFillColor(sf::Color::Blue);
	kruh.setOrigin(5, 5);
	kruh1.setRadius(10);
	kruh1.setFillColor(sf::Color::Blue);
	kruh1.setOrigin(5, 5);
	kruh2.setRadius(10);
	kruh2.setFillColor(sf::Color::Blue);
	kruh2.setOrigin(5, 5);


	if (!pTexture.loadFromFile("Images/armor.png"))
		std::cout << "Error could not load armor image" << std::endl;

	armorImage.setTexture(pTexture);
	armorImage1.setTexture(pTexture);

	armorImage.setOrigin((float)pTexture.getSize().x / 2, (float)pTexture.getSize().y / 2);
	armorImage1.setOrigin((float)pTexture.getSize().x / 2, (float)pTexture.getSize().y / 2);

	// Before it was 0.8 instead of 1.2
	armorImage1.setScale((float)1.2, (float)1.2);

	std::cout << "Armor created" << std::endl;
}

void armor::draw(sf::RenderWindow* Window, sf::Vector2f playerPosition, sf::Vector2u characterSize)
{
	// Set position
	armorImage.setPosition(playerPosition.x + (characterSize.x / 2), playerPosition.y + (characterSize.y / 2));
	armorImage1.setPosition(playerPosition.x + (characterSize.x / 2), playerPosition.y + (characterSize.y / 2));

	// Rotate
	if (rotateClock.getElapsedTime().asMilliseconds() > 10)
	{
		armorImage.rotate(1);
		armorImage1.rotate(-1);

		rotateClock.restart();
	}

	if (kruhClock.getElapsedTime().asMilliseconds() > 50)
	{
		float radius = 40;

		kruh.setPosition(playerPosition.x + (float)cos(rotace) * radius + (characterSize.x / 2) - 5, playerPosition.y + (float)sin(rotace) * radius + (characterSize.y / 2) - 5);
		kruh1.setPosition(playerPosition.x + (float)cos(rotace + 90) * radius + (characterSize.x / 2) - 5, playerPosition.y + (float)sin(rotace + 90) * radius + (characterSize.y / 2) - 5);
		kruh2.setPosition(playerPosition.x + (float)cos(rotace - 90) * radius + (characterSize.x / 2) - 5, playerPosition.y + (float)sin(rotace - 90) * radius + (characterSize.y / 2) - 5);
		rotace += (float)0.2;
		kruhClock.restart();
	}



	// Draw
	/*Window->draw(armorImage);
	Window->draw(armorImage1);*/
	Window->draw(kruh);
	Window->draw(kruh1);
	Window->draw(kruh2);
}

armor::~armor()
{
	std::cout << "Armor destructed" << std::endl;
}

sf::Time armor::getTime()
{
	return time.getElapsedTime();
}

double armor::getHP()
{
	return hp;
}