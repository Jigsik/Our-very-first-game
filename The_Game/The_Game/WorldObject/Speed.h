#include "Buff.h"

class Speed : public Buff
{
public:
	Speed();
	~Speed();
	void draw(sf::RenderWindow *Window);
	int speed = 3;

private:

};