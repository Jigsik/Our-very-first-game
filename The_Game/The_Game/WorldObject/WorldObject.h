#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>

#ifndef __WORLDOBJECT_H_INCLUDED__
#define __WORLDOBJECT_H_INCLUDED__

class WorldObject
{
public:
	WorldObject();
	~WorldObject();

	// Asi blbost
	//void draw(sf::RenderWindow* Window);

	// GET

	sf::Vector2u getSize();
	sf::Vector2f getPosition();
	sf::Sprite image;

private:

protected:
	sf::Texture pTexture;
	sf::Vector2u size, numberOfAnimations = sf::Vector2u(1, 1);
};

#endif // !__WORLDOBJECT_H_INCLUDED__