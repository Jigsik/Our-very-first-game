#include "Buff.h"

Buff::Buff()
{
	// TEXT TIME 

	// Text

	if (!gameFont.loadFromFile("Fonts/STENCIL.ttf"))
		std::cout << "Cannot load game Font" << std::endl;
	else std::cout << "Success loading game Font" << std::endl;

	text.setFont(gameFont);
	text.setCharacterSize(20);
}

Buff::~Buff()
{
}