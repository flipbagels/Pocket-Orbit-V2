#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Button.h"
#include "Circle.h"

class Level_2UI
{
private:
	sf::Vector2f pauseButtonPos;
	static constexpr float pauseButtonRadius = 40.0f;
	Button pauseButton;

	sf::Vector2f currentPlanetPos;
	static constexpr float currentPlanetRadius = 50.0f;
	Circle currentPlanet;


public:
	// Constructor / Destructor
	Level_2UI();
	Level_2UI(float width, float height, std::map<std::string, sf::Texture>& textureMap_in);
	~Level_2UI();

	// Functions
	bool isMouseOnUI(sf::RenderWindow& window_in) const;
	bool isPausePressed(sf::RenderWindow& window_in) const;
	void updateButtons(sf::RenderWindow& window_in);
	void setCurrentPlanetTexture(sf::Texture& texture_in);
	void render(sf::RenderTarget& target);
};