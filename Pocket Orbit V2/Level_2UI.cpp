#include "Level_2UI.h"


// Constructor / Destructor
Level_2UI::Level_2UI()
{
}

Level_2UI::Level_2UI(float width, float height, std::map<std::string, sf::Texture>& textureMap_in)
	:
	pauseButtonPos(sf::Vector2f(60.0f, 60.0f)),
	pauseButton(this->pauseButtonRadius, this->pauseButtonPos, textureMap_in["PauseButton"]),
	currentPlanetPos(sf::Vector2f(width - 60.0f, 60.0f)),
	currentPlanet(this->currentPlanetRadius, this->currentPlanetPos)
{
}

Level_2UI::~Level_2UI()
{
}

// Functions
bool Level_2UI::isMouseOnUI(sf::RenderWindow& window_in) const
{
	return (this->pauseButton.isMouseOnbutton(window_in));
}

bool Level_2UI::isPausePressed(sf::RenderWindow& window_in) const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || this->pauseButton.isPressed(window_in));
}

void Level_2UI::updateButtons(sf::RenderWindow& window_in)
{
	this->pauseButton.updateButtonMask(window_in);
}

void Level_2UI::setCurrentPlanetTexture(sf::Texture& texture_in)
{
	this->currentPlanet = Circle(this->currentPlanetRadius, this->currentPlanetPos);
	this->currentPlanet.shape.setTexture(&texture_in);
}

void Level_2UI::render(sf::RenderTarget& target)
{
	this->pauseButton.render(target);
	target.draw(this->currentPlanet.shape);
}