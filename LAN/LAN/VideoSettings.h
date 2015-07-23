#ifndef __VIDEOSETTINGS_H_INCLUDED__
#define __VIDEOSETTINGS_H_INCLUDED__

#include <SFML/Graphics.hpp>

class VideoSettings
{
public:
	VideoSettings();
	~VideoSettings();

	sf::Vector2u getScreenDimensions();
	void setScreenDimensions(sf::Vector2u);
	void setScreenDimensions(int width, int height);

	sf::Vector2u getScreenRatio();
private:
	sf::Vector2u screenDimensions;
	sf::Vector2u screenRatio;
};

#endif // !__VIDEOSETTINGS_H_INCLUDED__