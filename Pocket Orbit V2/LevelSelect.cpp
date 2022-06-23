#include "LevelSelect.h"


// Constructor / Destructor
LevelSelect::LevelSelect()
{
}

LevelSelect::LevelSelect(float width, float height, std::map<std::string, sf::Texture>& textureMap_in)
	:
	level_1Pos(sf::Vector2f(5.5 * width / 16, height / 4)),
	level_2Pos(sf::Vector2f(10.5 * width / 16, height / 4)),
	level_3Pos(sf::Vector2f(5.5 * width / 16, 3 * height / 4)),
	sandboxPos(sf::Vector2f(10.5 * width / 16, 3 * height / 4)),
	homeButtonPos(sf::Vector2f(60.0f, 60.0f)),
	level_1(this->levelSize, this->level_1Pos),
	level_1Comet(this->level_1CometRadius, this->level_1Pos),
	level_2(this->levelSize, this->level_2Pos),
	level_2Jupiter(this->level_2JupiterRadius, this->level_2Pos),
	level_3(this->levelSize, this->level_3Pos),
	level_3Earth(this->level_3EarthRadius, this->level_3Pos),
	sandbox(this->levelSize, this->sandboxPos),
	sandboxImage(this->sandboxImageSize, sf::Vector2f(this->sandboxPos.x, this->sandboxPos.y + 30.0f)),
	sandboxEarth(this->sandboxEarthRadius, sf::Vector2f(this->sandboxPos.x + 20.0f, this->sandboxPos.y + 10.0f)),
	sandboxUranus(this->sandboxUranusRadius, sf::Vector2f(this->sandboxPos.x - 50.0f, this->sandboxPos.y - 70.0f)),
	sandboxSatalite_red(this->sandboxSatalite_redRadius, sf::Vector2f(this->sandboxPos.x + 70.0f, this->sandboxPos.y - 70.0f)),
	homeButton(this->homeButtonRadius, this->homeButtonPos, textureMap_in["HomeButton"])
{
	// Level_1
	this->level_1.shape.setTexture(&textureMap_in["LevelSelectFrame-CometDash"]);
	this->level_1Comet.shape.setTexture(&textureMap_in["Comet"]);

	// Level_2
	this->level_2.shape.setTexture(&textureMap_in["LevelSelectFrame-PlanetDash"]);
	this->level_2Jupiter.shape.setTexture(&textureMap_in["Jupiter"]);

	// Level_3
	this->level_3.shape.setTexture(&textureMap_in["LevelSelectFrame-SaveEarth"]);
	this->level_3Earth.shape.setTexture(&textureMap_in["Earth"]);

	// Sandbox
	this->sandbox.shape.setTexture(&textureMap_in["LevelSelectFrame-Sandbox"]);
	this->sandboxImage.shape.setTexture(&textureMap_in["Sandbox"]);
	this->sandboxEarth.shape.setTexture(&textureMap_in["Earth"]);
	this->sandboxUranus.shape.setTexture(&textureMap_in["Uranus"]);
	this->sandboxSatalite_red.shape.setTexture(&textureMap_in["Satalite_red"]);

	// Sets Home Button
}

LevelSelect::~LevelSelect()
{
}

// Functions
void LevelSelect::reset(std::map<std::string, sf::Texture>& textureMap_in)
{
	this->level_1.shape.setTexture(&textureMap_in["LevelSelectFrame-CometDash"]);
	this->level_2.shape.setTexture(&textureMap_in["LevelSelectFrame-PlanetDash"]);
	this->level_3.shape.setTexture(&textureMap_in["LevelSelectFrame-SaveEarth"]);
	this->sandbox.shape.setTexture(&textureMap_in["LevelSelectFrame-Sandbox"]);
}

bool LevelSelect::isMouseOnUI(sf::RenderWindow& window_in) const
{
	return (this->homeButton.isPressed(window_in)
		|| this->level_1.isMouseOnRectangle(window_in)
		|| this->level_2.isMouseOnRectangle(window_in)
		|| this->level_3.isMouseOnRectangle(window_in)
		|| this->sandbox.isMouseOnRectangle(window_in));
}

bool LevelSelect::isLevelPressed(sf::RenderWindow& window_in) const
{
	return ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->level_1.isMouseOnRectangle(window_in))
		|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->level_2.isMouseOnRectangle(window_in))
		|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->level_3.isMouseOnRectangle(window_in))
		|| (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->sandbox.isMouseOnRectangle(window_in)));
}

std::string LevelSelect::whichLevel(sf::RenderWindow& window_in) const
{
	if (this->level_1.isMouseOnRectangle(window_in))
	{
		return "Level_1";
	}
	else if (this->level_2.isMouseOnRectangle(window_in))
	{
		return "Level_2";
	}
	else if (this->level_3.isMouseOnRectangle(window_in))
	{
		return "Level_3";
	}
	else if (this->sandbox.isMouseOnRectangle(window_in))
	{
		return "Sandbox";
	}
}

bool LevelSelect::isHomePressed(sf::RenderWindow& window_in) const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || this->homeButton.isPressed(window_in));
}

void LevelSelect::swapLevelSelectFrameTexture(sf::RenderWindow& window_in, std::map<std::string, sf::Texture>& textureMap_in, Rectangle& level_in, std::string level_name)
{
	if (level_in.isMouseOnRectangle(window_in))
	{
		if (level_name == "Level_1")
			level_in.shape.setTexture(&textureMap_in["LevelSelectFrameSelected-CometDash"]);
		if (level_name == "Level_2")
			level_in.shape.setTexture(&textureMap_in["LevelSelectFrameSelected-PlanetDash"]);
		if (level_name == "Level_3")
			level_in.shape.setTexture(&textureMap_in["LevelSelectFrameSelected-SaveEarth"]);
		if (level_name == "Sandbox")
			level_in.shape.setTexture(&textureMap_in["LevelSelectFrameSelected-Sandbox"]);
	}
	else
	{
		if (level_name == "Level_1")
			level_in.shape.setTexture(&textureMap_in["LevelSelectFrame-CometDash"]);
		if (level_name == "Level_2")
			level_in.shape.setTexture(&textureMap_in["LevelSelectFrame-PlanetDash"]);
		if (level_name == "Level_3")
			level_in.shape.setTexture(&textureMap_in["LevelSelectFrame-SaveEarth"]);
		if (level_name == "Sandbox")
			level_in.shape.setTexture(&textureMap_in["LevelSelectFrame-Sandbox"]);
	}
}

void LevelSelect::updateLevelSelectFrame(sf::RenderWindow& window_in, std::map<std::string, sf::Texture>& textureMap_in)
{
	this->swapLevelSelectFrameTexture(window_in, textureMap_in, this->level_1, "Level_1");
	this->swapLevelSelectFrameTexture(window_in, textureMap_in, this->level_2, "Level_2");
	this->swapLevelSelectFrameTexture(window_in, textureMap_in, this->level_3, "Level_3");
	this->swapLevelSelectFrameTexture(window_in, textureMap_in, this->sandbox, "Sandbox");
}

void LevelSelect::updateButtons(sf::RenderWindow& window_in)
{
	this->homeButton.updateButtonMask(window_in);
}

void LevelSelect::render(sf::RenderTarget& target)
{
	target.draw(this->level_1.shape);
	target.draw(this->level_1Comet.shape);
	target.draw(this->level_2.shape);
	target.draw(this->level_2Jupiter.shape);
	target.draw(this->level_3.shape);
	target.draw(this->level_3Earth.shape);
	target.draw(this->sandbox.shape);
	target.draw(this->sandboxEarth.shape);
	target.draw(this->sandboxUranus.shape);
	target.draw(this->sandboxSatalite_red.shape);
	target.draw(this->sandboxImage.shape);
	this->homeButton.render(target);
}