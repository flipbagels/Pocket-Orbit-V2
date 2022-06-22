#include "Level_1UI.h"


// Constructor / Destructor
Level_1UI::Level_1UI()
{
}

Level_1UI::Level_1UI(float width, float height, std::map<std::string, sf::Texture>& textureMap_in)
	:
	pauseButtonPos(sf::Vector2f(60.0f, 60.0f)),
	pauseButton(this->pauseButtonRadius, this->pauseButtonPos, textureMap_in["PauseButton"])
{
}

Level_1UI::~Level_1UI()
{
}

// Functions
bool Level_1UI::isMouseOnUI(sf::RenderWindow& window_in) const
{
	return (this->pauseButton.isMouseOnbutton(window_in));
}

bool Level_1UI::isPausePressed(sf::RenderWindow& window_in) const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || this->pauseButton.isPressed(window_in));
}

void Level_1UI::updateButtons(sf::RenderWindow& window_in)
{
	this->pauseButton.updateButtonMask(window_in);
}

void Level_1UI::render(sf::RenderTarget& target)
{
	this->pauseButton.render(target);
}