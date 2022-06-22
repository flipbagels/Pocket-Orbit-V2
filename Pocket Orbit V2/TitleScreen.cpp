#include "TitleScreen.h"
#include <cmath>

// Constructor / Destructor
TitleScreen::TitleScreen()
{
}

TitleScreen::TitleScreen(float xPos_in, float yPos_in, sf::Texture& titleTextTexture_in, sf::Texture& earthTexture_in, sf::Texture& startButtonTexture_in)
	:
	textPos(sf::Vector2f(xPos_in, yPos_in)),
	earthPos(sf::Vector2f(xPos_in + this->orbitCentre_dx, yPos_in + this->orbitCentre_dy - this->orbitRadius)),
	orbitCentre(sf::Vector2f(xPos_in + this->orbitCentre_dx, yPos_in + this->orbitCentre_dy)),
	startButtonPos(sf::Vector2f(xPos_in, yPos_in + 300.0f)),
	text(this->textSize, this->textPos),
	earth(this->earthRadius, this->earthPos),
	startButton(this->startButtonRadius, this->startButtonPos, startButtonTexture_in)
{
	// Sets Text
	this->text.shape.setTexture(&titleTextTexture_in);

	// Sets Earth
	this->earth.shape.setTexture(&earthTexture_in);

	// Sets Start Button
}

TitleScreen::~TitleScreen()
{
}

// Functions
void TitleScreen::reset()
{
	this->earthPos = sf::Vector2f(this->textPos.x + this->orbitCentre_dx, this->textPos.y + this->orbitCentre_dy - this->orbitRadius);
	this->earthVel = earthSpeed * sf::Vector2f(1.0f, 0.0f);
	this->earthRedTrail.clear();
}

bool TitleScreen::isMouseOnUI(sf::RenderWindow& window_in) const
{
	return (this->startButton.isMouseOnbutton(window_in));
}

bool TitleScreen::isStartPressed(sf::RenderWindow& window_in) const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || this->startButton.isPressed(window_in));
}

void TitleScreen::updateButtons(sf::RenderWindow& window_in)
{
	this->startButton.updateButtonMask(window_in);
}

void TitleScreen::updateEarth()
{
	this->earthPos += this->earthVel;
	sf::Vector2f normalPos = sf::Vector2f(this->earthPos - this->orbitCentre) / (sqrtf(pow(this->earthPos.x - this->orbitCentre.x, 2) + pow(this->earthPos.y - this->orbitCentre.y, 2)));
	this->earthPos = this->orbitCentre + (this->orbitRadius * normalPos);
	sf::Vector2f normalVel = sf::Vector2f(-(this->earthPos - this->orbitCentre).y, (this->earthPos - this->orbitCentre).x) / (sqrtf(pow(this->earthPos.x - this->orbitCentre.x, 2) + pow(this->earthPos.y - this->orbitCentre.y, 2)));
	this->earthVel = earthSpeed * normalVel;

	this->earth.shape.setPosition(this->earthPos);
}

void TitleScreen::updateEarthTrail()
{
	if (this->earthRedTrail.size() < this->earthRedTrailMax)
	{
		Circle red;
		red.shape.setOrigin(this->earthRadius, this->earthRadius);
		red.shape.setPosition(this->earthPos.x, this->earthPos.y);
		red.shape.setRadius(this->earthRadius);
		this->earthRedTrail.push_back(red);
	}
	else if (this->earthRedTrail.size() >= this->earthRedTrailMax)
	{
		this->earthRedTrail.erase(this->earthRedTrail.begin());
		Circle red;
		red.shape.setOrigin(this->earthRadius, this->earthRadius);
		red.shape.setPosition(this->earthPos.x, this->earthPos.y);
		red.shape.setRadius(this->earthRadius);
		this->earthRedTrail.push_back(red);
	}
	else
	{
	}

	for (int i = 0; i < this->earthRedTrail.size(); i++)
	{

		this->earthRedTrail[i].shape.setFillColor(sf::Color(255, 255, 255, 255 - (5 * (this->earthRedTrail.size() - i))));

	}
}

void TitleScreen::render(sf::RenderTarget& target)
{
	target.draw(this->text.shape);
	for (int i = 0; i < this->earthRedTrail.size(); i++)
	{
		target.draw(this->earthRedTrail[i].shape);
	}
	target.draw(this->earth.shape);
	this->startButton.render(target);
}