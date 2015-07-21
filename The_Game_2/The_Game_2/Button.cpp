#include "Button.h"

Button::Button()
{
}

void Button::initializeButton(std::string text, VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	horizontalCenter = (float)videoSettings->getScreenDimensions().x / 2;
	verticalCenter = (float)videoSettings->getScreenDimensions().y / 2;

	if (!setFont())
		; // TODO : Throw exception

	label.setFont(Font);
	label.setCharacterSize(fontSize);
	label.setString(text);
}

Button::~Button()
{
}

bool Button::setFont()
{
	if (!Font.loadFromFile(MenuManager::getFontLocation()))
	{
		std::cerr << "Error loading Font at location: " <<
			MenuManager::getFontLocation() << std::endl;
		return false; // Throw an exception
	}

	fontSize = MenuManager::getFontSize(videoSettings);

	return true;
}

void Button::setOrigin(std::string xPos, std::string yPos)
{
	float x, y;

	if (xPos == "CENTER")
		x = label.getLocalBounds().width / 2;
	else if (xPos == "LEFT")
		x = 0;
	else if (xPos == "RIGHT")
		x = label.getLocalBounds().width;
	else
		std::cerr << "Error in function setOrigin() (x) in class Button" << std::endl;

	if (xPos == "CENTER")
		y = label.getLocalBounds().height / 2;
	else if (xPos == "TOP")
		y = 0;
	else if (xPos == "BOTTOM")
		y = label.getLocalBounds().height;
	else
		std::cerr << "Error in function setOrigin() (y) in class Button" << std::endl;

	label.setOrigin(x, y);
}

void Button::setPosition(float x, float y)
{
	// This is going to bug if the width of the screen is 2px,
	// but that is not going to happen

	if (x == HORIZONTALCENTER)
		label.setPosition(horizontalCenter, y);
	else if (y == VERTICALCENTER)
		label.setPosition(x, verticalCenter);
	else
		label.setPosition(x, y);
}

void Button::setSelected(bool selected)
{
	this->selected = selected;

	if (selected)
		label.setColor(sf::Color(255, 0, 0, 255));
	else
		label.setColor(sf::Color(255, 255, 255, 255));
}

/*bool Button::isSelected()
{
	return selected;
}*/

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(label);
}