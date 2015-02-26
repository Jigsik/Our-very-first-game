#include <string>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>

class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map();
	~Map();
	bool load(const std::string& tileMapFile);

	sf::Vector2u getSize();

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	std::vector<int> tempMap;

	sf::Vector2u tileSize = sf::Vector2u(30, 30);

	unsigned width = 20, height = 20;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}
};