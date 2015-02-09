#include <SFML\Graphics.hpp>

class player
{
	public:
		player(double HP = 100, float speed = 1);
		void HP_minus(double damaged);
		double HP_left();
		sf::Sprite playerImage;
		sf::Texture pTexture;
		int move();
		float speed;

	private:
		double HP;
};