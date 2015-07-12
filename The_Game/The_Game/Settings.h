#ifndef __SETTINGS_H_INCLUDED__
#define __SETTINGS_H_INCLUDED__

#include <string>

class Settings
{
public:
	Settings();
	~Settings();

	std::string getMapLocation();
	std::string getFontLocation();
	std::string getMusicLocation();
	int getMusicVolume();
	int getRuneRespawnTime();
	int getRunesCount();

private:
	std::string mapLocation;
	std::string fontLocation;
	std::string musicLocation;
	int musicVolume;
	int runeRespawnTime;
	int runesCount;
};

#endif // !__SETTINGS_H_INCLUDED__