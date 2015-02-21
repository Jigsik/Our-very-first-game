#include "Rune.h"

Rune::Rune()
{
	//std::cout << "Rune Created" << std::endl;

	int type = rand() % 2;

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

	std::cout << a1 << std::endl << a2 << std::endl;

	image.setPosition(sf::Vector2f((float)a1, (float)a2));
}

Rune::~Rune()
{
	std::cout << "Rune Destroyed" << std::endl;
}