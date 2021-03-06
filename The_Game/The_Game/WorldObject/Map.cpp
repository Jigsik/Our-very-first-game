#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

sf::Vector2u Map::getSize()
{
	return sf::Vector2u((tempMap.size() / width) * tileSize.x, (tempMap.size() / height) * tileSize.y);
}

bool Map::load(const std::string& tileMapFile)
{
	std::ifstream tileFile(tileMapFile);

	if (tileFile.is_open())
	{
		std::string tileLocation;
		std::string tmpString, value;
		std::getline(tileFile, tileLocation);
		if (!m_tileset.loadFromFile(tileLocation))
			return false;

		// GET MAP WIDTH
		std::getline(tileFile, tmpString);
		std::stringstream stream(tmpString);
		std::getline(stream, value, '=');
		std::getline(stream, value);

		if (value.length() > 0)
			width = atoi(value.c_str());

		// GET MAP HEIGHT
		std::getline(tileFile, tmpString);
		std::stringstream stream1(tmpString);
		std::getline(stream1, value, '=');
		std::getline(stream1, value);

		if (value.length() > 0)
			height = atoi(value.c_str());

		// GET TILE WIDTH
		std::getline(tileFile, tmpString);
		std::stringstream stream2(tmpString);
		std::getline(stream2, value, '=');
		std::getline(stream2, value);

		if (value.length() > 0)
			tileSize.x = atoi(value.c_str());

		// GET TILE HEIGHT
		std::getline(tileFile, tmpString);
		std::stringstream stream3(tmpString);
		std::getline(stream3, value, '=');
		std::getline(stream3, value);

		if (value.length() > 0)
			tileSize.y = atoi(value.c_str());

		// resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		while (!tileFile.eof())
		{
			std::string str, value;
			std::getline(tileFile, str);
			std::stringstream stream(str);

			while (std::getline(stream, value, ','))
			{
				if (value.length() > 0)
					tempMap.push_back((atoi(value.c_str())) - 1);
			}
		}
	}

	for (unsigned i = 0; i < width; i++)
	{
		for (unsigned j = 0; j < height; j++)
		{
			if (tempMap[i+j*width] != -1)
			{
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				int tu = tempMap[i + j*width] % (m_tileset.getSize().x / tileSize.x);
				int tv = tempMap[i + j*width] / (m_tileset.getSize().x / tileSize.x);

				quad[0].position = sf::Vector2f((float)i * tileSize.x, (float)j * tileSize.y);
				quad[1].position = sf::Vector2f((float)(i + 1) * tileSize.x, (float)j * tileSize.y);
				quad[2].position = sf::Vector2f((float)(i + 1) * tileSize.x, (float)(j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f((float)i * tileSize.x, (float)(j + 1) * tileSize.y);

				quad[0].texCoords = sf::Vector2f((float)(tu)* tileSize.x, (float)tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((float)(tu + 1) * tileSize.x, (float)tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((float)(tu + 1) * tileSize.x, (float)(tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f((float)tu * tileSize.x, (float)(tv + 1) * tileSize.y);
			}
		}
	}

	return true;
}