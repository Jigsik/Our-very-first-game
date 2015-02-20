#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class WorldObject
{
public:
	WorldObject();
	~WorldObject();
	void draw(sf::RenderWindow* Window);

	// GET

	sf::Vector2u getSize();
	sf::Vector2f getPosition();

private:
	sf::Texture pTexture;
	sf::Sprite image;
	sf::Vector2u size;

protected:
	virtual void move();
	virtual void nextAnimation();
};

WorldObject::WorldObject()
{
}

WorldObject::~WorldObject()
{
}