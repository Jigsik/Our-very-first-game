#include "WorldObject.h"

WorldObject::WorldObject()
{
}

WorldObject::~WorldObject()
{
}

sf::Vector2u WorldObject::getSize()
{
	return sf::Vector2u(pTexture.getSize().x / numberOfAnimations.x, pTexture.getSize().y / numberOfAnimations.y);
}

sf::Vector2f WorldObject::getPosition()
{
	return sf::Vector2f(image.getPosition());
}