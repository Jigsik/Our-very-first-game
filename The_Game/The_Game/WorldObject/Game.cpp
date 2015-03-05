#include "Game.h"

Game::Game()
{
	Window = new sf::RenderWindow;

	Window->create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Hovnocuc", sf::Style::Fullscreen); // OK

	//screenDimensions = Window->getSize();

	Window->setMouseCursorVisible(false);

	screenDimensions.y = (screenDimensions.x * Window->getSize().y) / Window->getSize().x;

	setUpFont();
	setUpSound();

	if (!mapa.load("Maps/mapa.txt"))
		std::cout << "Failed to load map" << std::endl;
}

Game::~Game()
{
	// Delete rune if exists
	//if(rune)
		//delete rune;

	for (runesIt = runes.begin(); runesIt != runes.end();)
	{
		delete *runesIt;
		runesIt = runes.erase(runesIt);
	}

	// Delete Window
	if (Window)
		delete Window;

	// Delete all existing bullets
	for (bulletsIt = bullets.begin(); bulletsIt != bullets.end();)
	{
		delete *bulletsIt;
		bulletsIt = bullets.erase(bulletsIt);
	}
}

void Game::setUpFont()
{
	if (!gameFont.loadFromFile("Fonts/STENCIL.ttf"))
		std::cout << "Cannot load game Font" << std::endl;
	else std::cout << "Success loading game Font" << std::endl;

	fpsText.setFont(gameFont);
	fpsText.setCharacterSize((Window->getSize().x / screenDimensions.x) * 20);
	fpsText.setPosition(sf::Vector2f((float)Window->getSize().x - (Window->getSize().x / screenDimensions.x) * 50, 0));
}

void Game::setUpSound()
{
	if (!gameMusic.openFromFile("Sounds/music.wav"))
		std::cout << "Unable to load game Music." << std::endl;
	else std::cout << "Success loading game Music" << std::endl;

	gameMusic.setLoop(true);
	//gameMusic.play();
	gameMusic.setVolume(50);
}

void Game::countFPS()
{
	if (fpsClock.getElapsedTime().asMilliseconds() > 500)
	{
		fpsString = std::to_string(fps * 2);
		fpsClock.restart();
		fps = 0;
	}
	else fps++;

	fpsText.setString(fpsString);

	Window->setView(Window->getDefaultView());

	Window->draw(fpsText);

	//fpsText.setScale(Window->getSize().x / screenDimensions.x, Window->getSize().y / screenDimensions.y);
}

void Game::handlingRunes()
{
	/*if (!rune && runeClock.getElapsedTime().asSeconds() > 3)
	{
		rune = new Rune(mapa.getSize());
	}

	if (rune)
	{
		if (rune->runeClock.getElapsedTime().asSeconds() > rune->getDuration())
		{
			delete rune;
			rune = 0;
			runeClock.restart();
		}
	}*/

	if (runeClock.getElapsedTime().asMilliseconds() > 500)
	{
		// emplace_back()
		runes.push_back(new Rune(mapa.getSize()));
		runeClock.restart();
	}

	for (runesIt = runes.begin(); runesIt != runes.end();)
	{
		if ((*runesIt)->runeClock.getElapsedTime().asSeconds() > (*runesIt)->getDuration())
		{
			delete *runesIt;
			runesIt = runes.erase(runesIt);
		}
		else runesIt++;
	}
}

void Game::handlingBuffs()
{
	player.drawBuffs(Window, player1_view, player2_view, barView1, barView2);
}

void Game::handlingMissiles()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && bulletsClock.getElapsedTime().asMilliseconds() > 350)
	{
		bullets.push_back(new Bullet(player.getPosition(), player.getDirection(), player.getSize()));
		bulletsClock.restart();
	}

	for (bulletsIt = bullets.begin(); bulletsIt != bullets.end(); bulletsIt++)
	{
		(*bulletsIt)->changeState(Window);
	}
}

void Game::hanglingCharacters()
{
	Window->setView(barView1);
	player.changeState(Window);

	Window->setView(barView2);
	player.changeState(Window);
}

void Game::collisions()
{
	// Player and the rune

	float playerLeft = player.getPosition().x;
	float playerRight = player.getPosition().x + player.getSize().x;
	float playerTop = player.getPosition().y;
	float playerBottom = player.getPosition().y + player.getSize().y;

	for (runesIt = runes.begin(); runesIt != runes.end(); runesIt++)
	{
		float runeLeft = (*runesIt)->getPosition().x;
		float runeRight = (*runesIt)->getPosition().x + (*runesIt)->getSize().x;
		float runeTop = (*runesIt)->getPosition().y;
		float runeBottom = (*runesIt)->getPosition().y + (*runesIt)->getSize().y;
		
		if (playerLeft <= runeRight &&
			playerRight >= runeLeft &&
			playerTop <= runeBottom &&
			playerBottom >= runeTop)
		{
			// Get the rune type
			int runeType = (*runesIt)->getType();

			// Which rune have you taken?
			if (runeType == armorRune)
			{
				player.activateArmor();
			}
			else if (runeType == speedRune)
			{
				player.activateSpeed();
			}

			delete *runesIt;
			runesIt = runes.erase(runesIt);

			// If player get the rune, there is a big change that he is not getting any other
			// rune. So we can break here and control it later.
			break;
		}
	}
	
	/*if (rune)
	{
		float runeLeft = rune->getPosition().x;
		float runeRight = rune->getPosition().x + rune->getSize().x;
		float runeTop = rune->getPosition().y;
		float runeBottom = rune->getPosition().y + rune->getSize().y;

		if (playerLeft <= runeRight &&
			playerRight >= runeLeft &&
			playerTop <= runeBottom &&
			playerBottom >= runeTop)
		{
			// Get the rune type
			int runeType = rune->getType();

			// Which rune have you taken?
			if (runeType == armorRune)
			{
				player.activateArmor();
			}
			else if (runeType == speedRune)
			{
				player.activateSpeed();
			}

			// Clean memory, set rune to zero and restart the clock
			delete rune;
			rune = 0;
			runeClock.restart();
		}
	}*/
}

void Game::handlingViews()
{
	position.x = player.getPosition().x + player.getSize().x - (screenDimensions.x * 0.5f * 0.495f);
	position.y = player.getPosition().y + player.getSize().y - (screenDimensions.y * 0.5f * 0.95f);

	if (position.x <= 0)
		position.x = 0;
	else if (position.x > mapa.getSize().x - (screenDimensions.x * 0.495f))
		position.x = mapa.getSize().x - (screenDimensions.x * 0.495f);

	if (position.y <= 0)
		position.y = 0;
	else if (position.y > mapa.getSize().y - screenDimensions.y * 0.95f)
		position.y = mapa.getSize().y - screenDimensions.y * 0.95f;

	//player1_view.rotate(0.01f);

	/* VELIKA POZNAMKA
	   
	   player1_view.reset(sf::FloatRect(position.x, position.y, (float)(screenDimensions.x / 2), (float)screenDimensions.y));

	   Tento kod je spatne, protoze to view nema rozsah screenDimension.x / 2 a screenDimension.y...

	   Takhle to je spravne:

	   player2_view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x * 0.495f, screenDimensions.y * 0.95f));

	*/

	player1_view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x * 0.495f, screenDimensions.y * 0.95f));
	player2_view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x * 0.495f, screenDimensions.y * 0.95f));

	player1_view.zoom(0.5f);

	//std::cout << player1_view.getCenter().x << " " << player1_view.getCenter().y << std::endl;

	// previous line is just copied and set to view 2 so we can see tha same screen;

	//player1_view.move(0.01, 0.01)
}

void Game::draw()
{
	for (runesIt = runes.begin(); runesIt != runes.end(); runesIt++)
	{
		Window->setView(player1_view);
		Window->draw((*runesIt)->image);

		Window->setView(player2_view);
		Window->draw((*runesIt)->image);
	}

	/*if (rune)
	{
		Window->setView(player1_view);
		Window->draw(rune->image);

		Window->setView(player2_view);
		Window->draw(rune->image);
	}*/

	for (bulletsIt = bullets.begin(); bulletsIt != bullets.end(); bulletsIt++)
	{
		Window->setView(player1_view);
		Window->draw((*bulletsIt)->image);

		Window->setView(player2_view);
		Window->draw((*bulletsIt)->image);
	}

	Window->setView(player1_view);
	Window->draw(player.image);

	Window->setView(player2_view);
	Window->draw(player.image);
}

void Game::play()
{
	//player1_view.reset(sf::FloatRect(0, 0, (float)screenDimensions.x / 2, (float)screenDimensions.y));
	player1_view.setViewport(sf::FloatRect(0, 0, 0.495f, 0.95f));
	player2_view.setViewport(sf::FloatRect(0.505f, 0, 0.495f, 0.95f));
	barView1.setViewport(sf::FloatRect(0, 0.95f, 0.5f, 0.05f));
	barView2.setViewport(sf::FloatRect(0.5f, 0.95f, 0.5f, 0.05f));

	barView1.reset(sf::FloatRect(0, 0, (float)Window->getSize().x / 2, (float)Window->getSize().y / 20));
	barView2.reset(sf::FloatRect(0, 0, (float)Window->getSize().x / 2, (float)Window->getSize().y / 20));

	//player1_view.setCenter(300, 300);
	//player1_view.setSize(600, 600);

	//Window->setFramerateLimit(500); // OK

	//mapa.setScale(Window->getSize().x / screenDimensions.x, Window->getSize().y / screenDimensions.y);

	while (Window->isOpen()) // OK
	{
		Window->clear();


		Window->setView(player1_view);
		Window->draw(mapa);

		Window->setView(player2_view);
		Window->draw(mapa);

		Window->setView(player1_view);

		while (Window->pollEvent(gameEvent))
		{
			switch (gameEvent.type)
			{
			case sf::Event::KeyPressed:
				if (gameEvent.key.code == sf::Keyboard::Escape)
				{
					return;
				}
				else if (gameEvent.key.code == sf::Keyboard::P)
				{
					isPause = true;
				}
				break;
			case sf::Event::Resized:
				screenDimensions.x = gameEvent.size.width;
				screenDimensions.y = gameEvent.size.height;
				break;
			}
		}

		collisions();
		handlingRunes();
		handlingBuffs();
		Window->setView(player1_view);
		handlingMissiles();
		hanglingCharacters();
	
		draw();

		countFPS();

		Window->setView(player1_view);

		handlingViews();
		Window->display();
	}

	gameMusic.stop();

	Window->close(); // OK
}