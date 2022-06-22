#include "PostGameUI.h"


// Constructor / Destructor
PostGameUI::PostGameUI()
{
}

PostGameUI::PostGameUI(sf::Font& font_in, sf::VideoMode videoMode_in, std::map<std::string, sf::Texture>& textureMap_in)
	:
	mask(sf::Vector2f(videoMode_in.width, videoMode_in.height), sf::Vector2f(videoMode_in.width, videoMode_in.height) / 2.0f),
	postGameTextPos(float(videoMode_in.width / 2) - 230.0f, 300.0f),
	levelSelectButtonPos(sf::Vector2f((videoMode_in.width / 2) - 75.0f, videoMode_in.height / 2)),
	levelSelectButton(this->levelSelectButtonRadius, this->levelSelectButtonPos, textureMap_in["LevelSelectButton"]),
	restartButtonPos(sf::Vector2f((videoMode_in.width / 2) + 75.0f, videoMode_in.height / 2)),
	restartButton(this->restartButtonRadius, this->restartButtonPos, textureMap_in["RestartButton"])
{
	this->mask.shape.setFillColor(sf::Color(0, 0, 0, 100));

	this->postGameText.setFont(font_in);
	this->postGameText.setCharacterSize(75);
	this->postGameText.setStyle(sf::Text::Bold);
	this->postGameText.setFillColor(sf::Color::White);
	this->postGameText.setPosition(this->postGameTextPos);
}

PostGameUI::~PostGameUI()
{
}

// Functions
void PostGameUI::beginPostGame()
{
	this->postGameBool = true;
}

void PostGameUI::endPostGame()
{
	this->postGameBool = false;
}

bool PostGameUI::isPostGameActive() const
{
	return this->postGameBool;
}

bool PostGameUI::isMouseOnUI(sf::RenderWindow& window_in) const
{
	return (this->levelSelectButton.isMouseOnbutton(window_in)
		|| this->restartButton.isMouseOnbutton(window_in));
}

void PostGameUI::updateButtons(sf::RenderWindow& window_in)
{
	this->levelSelectButton.updateButtonMask(window_in);
	this->restartButton.updateButtonMask(window_in);
}

bool PostGameUI::isLevelSelectPressed(sf::RenderWindow& window_in) const
{
	return (this->levelSelectButton.isPressed(window_in));
}

bool PostGameUI::isRestartPressed(sf::RenderWindow& window_in) const
{
	return (this->restartButton.isPressed(window_in));
}

void PostGameUI::render(sf::RenderTarget& target, Score score_in)
{
	target.draw(this->mask.shape);
	this->levelSelectButton.render(target);
	this->restartButton.render(target);

	std::ostringstream ss;
	ss << "Your score: " << score_in.getScoreCounter();

	this->postGameText.setString(ss.str());

	target.draw(this->postGameText);
}