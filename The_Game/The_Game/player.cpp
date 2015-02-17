#include "player.h"

player::player(double _hp, float _speed)
: HP(_hp), speed(_speed)
{
	// Texture

	if (!pTexture.loadFromFile("Images/player_1.png"))
		std::cout << "Error could not load player image." << std::endl;

	playerImage.setTexture(pTexture);

	characterSize.x = pTexture.getSize().x;
	characterSize.y = pTexture.getSize().y / 4;

	// Walk sound

	if (!walkBuffer.loadFromFile("Sounds/walk.wav"))
		std::cout << "Error could not load walk sound." << std::endl;

	walk.setBuffer(walkBuffer);
	walk.setLoop(true);

	// Sprint sound

	if (!sprintBuffer.loadFromFile("Sounds/sprint.wav"))
		std::cout << "Error could not load sprint sound." << std::endl;

	sprintSound.setBuffer(sprintBuffer);
	sprintSound.setLoop(true);

	std::cout << "Player created" << std::endl;

	source = sf::Vector2u(1, Down);
	rocket_direction = sf::Vector2i(0,1);
}

player::~player()
{
	if (brneni)
	{
		brneni->~armor();
		delete brneni;
	}
}

void player::activateArmor()
{
	brneni = new armor;
}

void player::HP_minus(double damaged)
{
	HP -= damaged;
}

double player::HP_left()
{
	return HP;
}

void player::nextAnimation()
{
	// Go to next animation
	source.x++;

	// Reset Clock
	animationClock.restart();
}

void player::draw(sf::RenderWindow* Window)
{
	if (brneni)
	{
		if (brneni->getTime().asSeconds() > 10)
		{
			brneni->~armor();
			brneni = 0;
		}
		else {
			brneni->draw(Window, playerImage.getPosition(), characterSize);
		}
	}

	if (moveClock.getElapsedTime().asMilliseconds() > 10
		&& playerImage.getPosition().x >= 0
		&& playerImage.getPosition().y >= 0
		&& playerImage.getPosition().x <= Window->getSize().x - characterSize.x
		&& playerImage.getPosition().y <= Window->getSize().y - characterSize.y)
		player::move();

	if (playerImage.getPosition().x < 0) playerImage.setPosition(playerImage.getPosition().x + 1, playerImage.getPosition().y);
	else if (playerImage.getPosition().y < 0) playerImage.setPosition(playerImage.getPosition().x, playerImage.getPosition().y + 1);
	else if (playerImage.getPosition().x > Window->getSize().x - characterSize.x) playerImage.setPosition(playerImage.getPosition().x - 1, playerImage.getPosition().y);
	else if (playerImage.getPosition().y > Window->getSize().y - characterSize.y) playerImage.setPosition(playerImage.getPosition().x, playerImage.getPosition().y - 1);

	if (animationClock.getElapsedTime().asMilliseconds() > (400 / speed))
		player::nextAnimation();

	if (source.x * characterSize.x >= pTexture.getSize().x)
		source.x = 0;

	playerImage.setTextureRect(sf::IntRect(source.x * characterSize.x, source.y * characterSize.y, characterSize.x, characterSize.y));

	Window->draw(playerImage);
}

void player::move()
{
	// Movement speed
	speed = 1,5;

	// Increasing movement speed

	// Playing the walk sound

	walk.pause();
	sprintSound.pause();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		speed *= 2;
		walk.stop();
		sprintSound.play();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sprintSound.stop();
		walk.play();

	}
	
	// Player movement

	float diag_speed = sqrt((speed*speed)/2);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerImage.move(-diag_speed, -diag_speed);
		source.y = Up;
		rocket_direction = sf::Vector2i(-1, -1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerImage.move(diag_speed, -diag_speed);
		source.y = Up;
		rocket_direction = sf::Vector2i(1, -1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerImage.move(diag_speed, diag_speed);
		source.y = Down;
		rocket_direction = sf::Vector2i(1, 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerImage.move(-diag_speed, diag_speed);
		source.y = Down;
		rocket_direction = sf::Vector2i(-1, 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerImage.move(0, -speed);
		source.y = Up;
		rocket_direction = sf::Vector2i(0, -1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		playerImage.move(0, speed);
		source.y = Down;
		rocket_direction = sf::Vector2i(0, 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerImage.move(-speed, 0);
		source.y = Left;
		rocket_direction = sf::Vector2i(-1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerImage.move(speed, 0);
		source.y = Right;
		rocket_direction = sf::Vector2i(1, 0);
	}

	// Reset Clock

	moveClock.restart();
}