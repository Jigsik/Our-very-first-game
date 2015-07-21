#ifndef __MENUMANAGER_H_INCLUDED__
#define __MENUMANAGER_H_INCLUDED__

#include <iostream>
#include "VideoSettings.h"

class MenuManager
{
public:
	MenuManager();
	~MenuManager();

	static std::string	getBackgroundLocation();
	static std::string	getFontLocation();
	static unsigned		getFontSize(VideoSettings *videoSettings);
};

#endif // !__MENUMANAGER_H_INCLUDED__