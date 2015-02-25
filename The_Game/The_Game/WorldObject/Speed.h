#include "Buff.h"

class Speed : public Buff
{
public:
	Speed();
	~Speed();
	void draw(sf::RenderWindow *Window);
	float speed = 1.5f;

private:

};