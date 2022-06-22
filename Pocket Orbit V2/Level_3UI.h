#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Button.h"

class Level_3UI
{
private:
	sf::Vector2f pauseButtonPos;
	static constexpr float pauseButtonRadius = 40.0f;
	Button pauseButton;

public:
	// Constructor / Destructor
	Level_3UI();
	Level_3UI(float width, float height, std::map<std::string, sf::Texture>& textureMap_in);
	~Level_3UI();

	// Functions
	bool isMouseOnUI(sf::RenderWindow& window_in) const;
	bool isPausePressed(sf::RenderWindow& window_in) const;
	void updateButtons(sf::RenderWindow& window_in);
	void render(sf::RenderTarget& target);
};