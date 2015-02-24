#include "Player1.h"

Player::Player(int _hp, float _speed)
: Character(_hp, _speed)
{
	numberOfAnimations = sf::Vector2u(1, 4);

	// Texture

	if (!pTexture.loadFromFile("Images/player_1.png"))
		std::cout << "Error could not load player image." << std::endl;

	image.setTexture(pTexture);
	size.x = pTexture.getSize().x / numberOfAnimations.x;
	size.y = pTexture.getSize().y / numberOfAnimations.y;

	image.setPosition(150, 150);

	// Sounds

	if (!walkBuffer.loadFromFile("Sounds/walk.wav"))
		std::cout << "Error could not load walk sound." << std::endl;

	walkSound.setBuffer(walkBuffer);
	walkSound.setLoop(true);

	if (!sprintBuffer.loadFromFile("Sounds/sprint.wav"))
		std::cout << "Error could not load sprint sound." << std::endl;

	sprintSound.setBuffer(sprintBuffer);
	sprintSound.setLoop(true);

	// Speed

	moveSpeed = 1;

	// Texts

	if (!gameFont.loadFromFile("Fonts/STENCIL.ttf"))
		std::cout << "Cannot load game Font" << std::endl;
	else std::cout << "Success loading game Font" << std::endl;

	text.setFont(gameFont);
	text.setCharacterSize(20);

	// Player has been succesfully created

	std::cout << "Player created" << std::endl;
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow *Window)
{
	if (moveClock.getElapsedTime().asMilliseconds() > 10)
		move();

	if (animationClock.getElapsedTime().asMilliseconds() > (400 / speed))
		nextAnimation();

	if (source.x * size.x >= pTexture.getSize().x)
		source.x = 0;

	image.setTextureRect(sf::IntRect(source.x * size.x, source.y * size.y, size.x, size.y));

	Window->draw(image);

	// Texts

	text.setPosition(sf::Vector2f(0, 0));
	string = std::to_string(HP);
	text.setString("HP = " + string);

	Window->setView(Window->getDefaultView());

	Window->draw(text);

	if (armor)
	{
		text.setPosition(sf::Vector2f(100, 0));
		string = std::to_string(armor->getHP());
		text.setString("Armor = " + string);
		Window->draw(text);
	}
}

void Player::move()
{
	if (sf::Keyboard::isKeyPressed(sprintKey))
	{
		speed = moveSpeed * 2;
	}
	else speed = moveSpeed;

	float diagonalSpeed = sqrt((speed*speed) / 2);

	if (sf::Keyboard::isKeyPressed(upKey) && sf::Keyboard::isKeyPressed(leftKey))
	{
		image.move(-diagonalSpeed, -diagonalSpeed);
		source.y = Up;
		direction = sf::Vector2i(-1, -1);
	}
	else if (sf::Keyboard::isKeyPressed(upKey) && sf::Keyboard::isKeyPressed(rightKey))
	{
		image.move(diagonalSpeed, -diagonalSpeed);
		source.y = Up;
		direction = sf::Vector2i(1, -1);
	}
	else if (sf::Keyboard::isKeyPressed(downKey) && sf::Keyboard::isKeyPressed(leftKey))
	{
		image.move(-diagonalSpeed, diagonalSpeed);
		source.y = Down;
		direction = sf::Vector2i(-1, 1);
	}
	else if (sf::Keyboard::isKeyPressed(downKey) && sf::Keyboard::isKeyPressed(rightKey))
	{
		image.move(diagonalSpeed, diagonalSpeed);
		source.y = Down;
		direction = sf::Vector2i(1, 1);
	}
	else if (sf::Keyboard::isKeyPressed(upKey))
	{
		image.move(0, -speed);
		source.y = Up;
		direction = sf::Vector2i(0, -1);
	}
	else if (sf::Keyboard::isKeyPressed(downKey))
	{
		image.move(0, speed);
		source.y = Down;
		direction = sf::Vector2i(0, 1);
	}
	else if (sf::Keyboard::isKeyPressed(leftKey))
	{
		image.move(-speed, 0);
		source.y = Left;
		direction = sf::Vector2i(-1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(rightKey))
	{
		image.move(speed, 0);
		source.y = Right;
		direction = sf::Vector2i(1, 0);
	}

	moveClock.restart();
}