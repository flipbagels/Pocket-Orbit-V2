#include "Level_3UI.h"


// Constructor / Destructor
Level_3UI::Level_3UI()
{
}

Level_3UI::Level_3UI(float width, float height, std::map<std::string, sf::Texture>& textureMap_in)
	:
	pauseButtonPos(sf::Vector2f(60.0f, 60.0f)),
	pauseButton(this->pauseButtonRadius, this->pauseButtonPos, textureMap_in["PauseButton"])
{
}

Level_3UI::~Level_3UI()
{
}

// Functions
bool Level_3UI::isMouseOnUI(sf::RenderWindow& window_in) const
{
	return (this->pauseButton.isMouseOnbutton(window_in));
}

bool Level_3UI::isPausePressed(sf::RenderWindow& window_in) const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || this->pauseButton.isPressed(window_in));
}

void Level_3UI::updateButtons(sf::RenderWindow& window_in)
{
	this->pauseButton.updateButtonMask(window_in);
}

void Level_3UI::render(sf::RenderTarget& target)
{
	this->pauseButton.render(target);
}