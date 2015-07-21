#include "MenuScreen.h"

void MenuScreen::resolutionChanged()
{
	backgroundImage.setScale(
		videoSettings->getScreenDimensions().x / backgroundImage.getLocalBounds().width,
		videoSettings->getScreenDimensions().y / backgroundImage.getLocalBounds().height);

	fontSize = MenuManager::getFontSize(videoSettings);
}

bool MenuScreen::setBackground()
{
	if (!backgroundTexture.loadFromFile(MenuManager::getBackgroundLocation()))
	{
		std::cerr << "Error loading Texture at location: " <<
			MenuManager::getBackgroundLocation() << std::endl;
		return false; // Throw an exception
	}
	backgroundImage.setTexture(backgroundTexture);
	backgroundImage.setScale(
		videoSettings->getScreenDimensions().x / backgroundImage.getLocalBounds().width,
		videoSettings->getScreenDimensions().y / backgroundImage.getLocalBounds().height);
	
	return true;
}

bool MenuScreen::setFont()
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