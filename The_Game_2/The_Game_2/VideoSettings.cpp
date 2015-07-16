#include "VideoSettings.h"


VideoSettings::VideoSettings()
{
	screenDimensions = sf::Vector2u(640, 360);
	screenRatio = sf::Vector2u(16, 9);
}


VideoSettings::~VideoSettings()
{
}

sf::Vector2u VideoSettings::getScreenDimensions()
{
	return screenDimensions;
}

sf::Vector2u VideoSettings::getScreenRatio()
{
	return screenRatio;
}

void VideoSettings::setScreenDimensions(sf::Vector2u newScreenDimensions)
{
	screenDimensions = newScreenDimensions;
}

void VideoSettings::setScreenDimensions(int width, int height)
{
	screenDimensions = sf::Vector2u(width, height);
}