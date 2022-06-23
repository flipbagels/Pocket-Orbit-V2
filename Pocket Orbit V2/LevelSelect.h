#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Rectangle.h"
#include "Circle.h"
#include "Button.h"

class LevelSelect
{
private:
	// All Levels
	sf::Vector2f levelSize = sf::Vector2f(390.0f, 390.0f);

	// Level 1
	sf::Vector2f level_1Pos;
	Rectangle level_1;
	static constexpr float level_1CometRadius = 80.0f;
	Circle level_1Comet;

	// Level 2
	sf::Vector2f level_2Pos;
	Rectangle level_2;
	static constexpr float level_2JupiterRadius = 80.0f;
	Circle level_2Jupiter;

	// Level 3
	sf::Vector2f level_3Pos;
	Rectangle level_3;
	static constexpr float level_3EarthRadius = 80.0f;
	Circle level_3Earth;

	// Sandbox
	sf::Vector2f sandboxPos;
	Rectangle sandbox;
	sf::Vector2f sandboxImageSize = sf::Vector2f(210.0f, 140.0f);
	Rectangle sandboxImage;
	static constexpr float sandboxEarthRadius = 30.0f;
	Circle sandboxEarth;
	static constexpr float sandboxUranusRadius = 50.0f;
	Circle sandboxUranus;
	static constexpr float sandboxSatalite_redRadius = 25.0f;
	Circle sandboxSatalite_red;

	// Home Button
	sf::Vector2f homeButtonPos;
	static constexpr float homeButtonRadius = 40.0f;
	Button homeButton;


public:
	// Constructor / Destructor
	LevelSelect();
	LevelSelect(float width, float height, std::map<std::string, sf::Texture>& textureMap_in);
	~LevelSelect();

	// Functions
	void reset(std::map<std::string, sf::Texture>& textureMap_in);
	bool isMouseOnUI(sf::RenderWindow& window_in) const;
	bool isLevelPressed(sf::RenderWindow& window_in) const;
	std::string whichLevel(sf::RenderWindow& window_in) const;
	bool isHomePressed(sf::RenderWindow& window_in) const;
	void swapLevelSelectFrameTexture(sf::RenderWindow& window_in, std::map<std::string, sf::Texture>& textureMap_in, Rectangle& level_in, std::string level_name);
	void updateLevelSelectFrame(sf::RenderWindow& window_in, std::map<std::string, sf::Texture>& textureMap_in);
	void updateButtons(sf::RenderWindow& window_in);
	void render(sf::RenderTarget& target);
};