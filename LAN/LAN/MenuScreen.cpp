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

void MenuScreen::setButtons()
{
	float verticalPos = (float)videoSettings->getScreenDimensions().y / 5;
	float verticalRatio = (float)videoSettings->getScreenDimensions().y / 5;

	for (buttonsIt = buttons.begin(); buttonsIt != buttons.end(); buttonsIt++)
	{
		(*buttonsIt)->setOrigin("CENTER", "CENTER");
		(*buttonsIt)->setPosition((float)(*buttonsIt)->HORIZONTALCENTER, verticalPos);

		verticalPos += verticalRatio;
	}
}

void MenuScreen::setButtonsSelectedALL(bool selected)
{
	for (buttonsIt = buttons.begin(); buttonsIt != buttons.end(); buttonsIt++)
	{
		(*buttonsIt)->setSelected(selected);
	}
}

void MenuScreen::draw(sf::RenderWindow &App)
{
	//Clearing screen
	App.clear();

	//Drawing
	App.draw(backgroundImage);

	for (buttonsIt = buttons.begin(); buttonsIt != buttons.end(); buttonsIt++)
	{
		App.draw(*(*buttonsIt));
	}

	App.display();
}