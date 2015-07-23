#ifndef __BUTTON_H_INCLUDED__
#define __BUTTON_H_INCLUDED__

#include <SFML\Graphics.hpp>
#include "MenuManager.h"

class Button : public sf::Drawable
{
public:
	Button();
	~Button();
	void initializeButton(std::string text, VideoSettings *videoSettings);
	void setOrigin(std::string xPos, std::string yPos);
	void setPosition(float x, float y);
	void setSelected(bool selected);
	//bool isSelected();

	enum Pos { HORIZONTALCENTER, VERTICALCENTER };

private:
	// draw
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Settings
	VideoSettings *videoSettings;

	sf::Text label;
	sf::Font Font;
	unsigned fontSize;

	float horizontalCenter;
	float verticalCenter;

	bool selected;

	bool setFont();
};

#endif // !__BUTTON_H_INCLUDED__