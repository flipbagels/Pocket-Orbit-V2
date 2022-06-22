#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Circle.h"


class Button
{
private:
	Circle button;
	Circle mask;
	Circle outline;
	static constexpr float outlineThickness = 5.0f;

public:
	// Constructor / Destructor
	Button();
	Button(float radius_in, sf::Vector2f position_in, sf::Texture& texture_in);
	~Button();

	// Functions
	void setSpacedOutlineColor(sf::Color color);
	bool isMouseOnbutton(sf::RenderWindow& window_in) const;
	bool isPressed(sf::RenderWindow& window_in) const;
	void updateButtonMask(sf::RenderWindow& window_in);
	void updateButtonSpacedOutline(sf::RenderWindow& window_in);
	void render(sf::RenderTarget& target);
};
