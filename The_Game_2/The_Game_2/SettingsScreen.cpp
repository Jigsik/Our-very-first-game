#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(VideoSettings *videoSettings)
{
	this->videoSettings = videoSettings;

	if (!Texture.loadFromFile("Images/menuPic.jpg"))
	{
		std::cerr << "Error loading menuPic" << std::endl;
		// Throw an exception
	}
	Sprite.setTexture(Texture);
	Sprite.setScale(
		videoSettings->getScreenDimensions().x / Sprite.getLocalBounds().width,
		videoSettings->getScreenDimensions().y / Sprite.getLocalBounds().height);

	if (!Font.loadFromFile("Fonts/STENCIL.ttf"))
	{
		std::cerr << "Error loading STENCIL.ttf" << std::endl;
		// Throw an exception
	}

	int fontSize = videoSettings->getScreenDimensions().y / 10;
	float horizontalCenter = (float)videoSettings->getScreenDimensions().x / 2;
	float verticalPos = (float)videoSettings->getScreenDimensions().y / 10;
	float verticalRatio = (float)videoSettings->getScreenDimensions().y / 10;

	float resPos = (float)videoSettings->getScreenDimensions().x / 10;
	float resStartPos = (float)videoSettings->getScreenDimensions().x / 10;
	float resRatio = (float)videoSettings->getScreenDimensions().x / 5;

	resolutionLabel.setFont(Font);
	resolutionLabel.setCharacterSize(fontSize);
	resolutionLabel.setString("Resolution");
	resolutionLabel.setOrigin(resolutionLabel.getLocalBounds().width / 2, resolutionLabel.getLocalBounds().height / 2);
	resolutionLabel.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	res1.setFont(Font);
	res1.setCharacterSize(fontSize / 2);
	res1.setString("1920x1080");
	res1.setPosition(resPos, verticalPos);

	resPos += resRatio;

	res2.setFont(Font);
	res2.setCharacterSize(fontSize / 2);
	res2.setString("1366x768");
	res2.setPosition(resPos, verticalPos);

	verticalPos += verticalRatio;

	ratioLabel.setFont(Font);
	ratioLabel.setCharacterSize(fontSize);
	ratioLabel.setString("Ratio");
	ratioLabel.setOrigin(ratioLabel.getLocalBounds().width / 2, ratioLabel.getLocalBounds().height / 2);
	ratioLabel.setPosition(horizontalCenter, verticalPos);

	verticalPos += verticalRatio;

	ratio1.setFont(Font);
	ratio1.setCharacterSize(fontSize / 2);
	ratio1.setString("16:9");
	ratio1.setPosition(resStartPos, verticalPos);

	verticalPos += verticalRatio;

	applyLabel.setFont(Font);
	applyLabel.setCharacterSize(fontSize);
	applyLabel.setString("Apply");
	applyLabel.setOrigin(applyLabel.getLocalBounds().width, 0);
	applyLabel.setPosition(horizontalCenter - (float)videoSettings->getScreenDimensions().x / 10, verticalPos);
	
	cancelLabel.setFont(Font);
	cancelLabel.setCharacterSize(fontSize);
	cancelLabel.setString("Cancel");
	cancelLabel.setPosition(horizontalCenter + (float)videoSettings->getScreenDimensions().x / 10, verticalPos);
}


SettingsScreen::~SettingsScreen()
{
}

int SettingsScreen::Run(sf::RenderWindow &App)
{
	while (true)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Return:
					return 0;
					break;
				default:
					break;
				}
			}
		}

		
		//Clearing screen
		App.clear();

		//Drawing
		App.draw(Sprite);
		App.draw(resolutionLabel);
		App.draw(res1);
		App.draw(res2);
		App.draw(ratioLabel);
		App.draw(ratio1);
		App.draw(applyLabel);
		App.draw(cancelLabel);
		App.display();
	}
}