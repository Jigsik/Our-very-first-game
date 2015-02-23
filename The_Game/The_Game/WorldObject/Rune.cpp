#include "Rune.h"

Rune::Rune()
{
	//std::cout << "Rune Created" << std::endl;

	type = rand() % numberOfRunes;

	// Texture

	if (type == armorRune)
	{
		if (!pTexture.loadFromFile("Images/armor_rune.png"))
			std::cout << "Error could not load ArmorRune image." << std::endl;

		std::cout << "ArmorRune created" << std::endl;
	}
	else if (type == speedRune)
	{
		if (!pTexture.loadFromFile("Images/speed_rune.png"))
			std::cout << "Error could not load ArmorRune image." << std::endl;

		std::cout << "SpeedRune created" << std::endl;
	}

	image.setTexture(pTexture);

	int a1 = rand() % (600 - getSize().x);
	int a2 = rand() % (400 - getSize().y);

	image.setPosition(sf::Vector2f((float)a1, (float)a2));
}

int Rune::getType()
{
	return type;
}

int Rune::getDuration()
{
	return duration;
}

Rune::~Rune()
{
	std::cout << "Rune Destroyed" << std::endl;
}