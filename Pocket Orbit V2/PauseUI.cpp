#include "PauseUI.h"


// Constructor / Destructor
PauseUI::PauseUI()
{
}

PauseUI::PauseUI(sf::VideoMode videoMode_in, std::map<std::string, sf::Texture>& textureMap_in)
	:
	mask(sf::Vector2f(videoMode_in.width, videoMode_in.height), sf::Vector2f(videoMode_in.width, videoMode_in.height) / 2.0f),
	levelSelectButtonPos(sf::Vector2f((videoMode_in.width / 2) - 150.0f, videoMode_in.height / 2)),
	levelSelectButton(this->levelSelectButtonRadius, this->levelSelectButtonPos, textureMap_in["LevelSelectButton"]),
	restartButtonPos(sf::Vector2f(videoMode_in.width / 2, videoMode_in.height / 2)),
	restartButton(this->restartButtonRadius, this->restartButtonPos, textureMap_in["RestartButton"]),
	startButtonPos(sf::Vector2f((videoMode_in.width / 2) + 150.0f, videoMode_in.height / 2)),
	startButton(this->startButtonRadius, this->startButtonPos, textureMap_in["StartButton"])
{
	this->mask.shape.setFillColor(sf::Color(0, 0, 0, 100));
}

PauseUI::~PauseUI()
{
}

// Functions
void PauseUI::doPause()
{
	this->pause = true;
}

void PauseUI::unPause()
{
	this->pause = false;
}

bool PauseUI::isPaused() const
{
	return this->pause;
}

bool PauseUI::isMouseOnUI(sf::RenderWindow& window_in) const
{
	return (this->levelSelectButton.isMouseOnbutton(window_in)
		|| this->restartButton.isMouseOnbutton(window_in)
		|| this->startButton.isMouseOnbutton(window_in));
}

void PauseUI::updateButtons(sf::RenderWindow& window_in)
{
	this->levelSelectButton.updateButtonMask(window_in);
	this->restartButton.updateButtonMask(window_in);
	this->startButton.updateButtonMask(window_in);
}

bool PauseUI::isLevelSelectPressed(sf::RenderWindow& window_in) const
{
	return (this->levelSelectButton.isPressed(window_in));
}

bool PauseUI::isRestartPressed(sf::RenderWindow& window_in) const
{
	return (this->restartButton.isPressed(window_in));
}

bool PauseUI::isStartPressed(sf::RenderWindow& window_in) const
{
	return (this->startButton.isPressed(window_in));
}

void PauseUI::render(sf::RenderTarget& target)
{
	target.draw(this->mask.shape);
	this->levelSelectButton.render(target);
	this->restartButton.render(target);
	this->startButton.render(target);
}