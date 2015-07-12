#include "Settings.h"

Settings::Settings()
{
	mapLocation = "Maps/mapa.txt";
	
	fontLocation = "Fonts/STENCIL.ttf";
	
	musicLocation = "Sounds/music.wav";
	musicVolume = 50;

	runeRespawnTime = 500;
	runesCount = 2;
}

Settings::~Settings()
{

}

std::string Settings::getMapLocation()
{
	return mapLocation;
}

std::string Settings::getFontLocation()
{
	return fontLocation;
}

std::string Settings::getMusicLocation()
{
	return musicLocation;
}

int Settings::getMusicVolume()
{
	return musicVolume;
}

int Settings::getRuneRespawnTime()
{
	return runeRespawnTime;
}

int Settings::getRunesCount()
{
	return runesCount;
}