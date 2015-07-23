#include "MenuManager.h"

MenuManager::MenuManager()
{
}


MenuManager::~MenuManager()
{
}

std::string MenuManager::getBackgroundLocation()
{
	return "Images/menuPic.jpg";
}

std::string MenuManager::getFontLocation()
{
	return "Fonts/STENCIL.ttf";
}

unsigned MenuManager::getFontSize(VideoSettings *videoSettings)
{
	return videoSettings->getScreenDimensions().y / 10;
}