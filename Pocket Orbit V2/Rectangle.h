#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <cmath>

#include "PanZoom.h"

class Rectangle
{
public:
	// Public Member Variables
	sf::RectangleShape shape;

	// Constructor / Destructor
	Rectangle();
	Rectangle(sf::Vector2f size_in, sf::Vector2f position_in);
	~Rectangle();

	// Functions
	bool isMouseOnRectangle(sf::RenderWindow& window_in) const;
	bool isMouseOnWorldRectangle(sf::RenderWindow& window_in, PanZoom panZoom_in) const;
};