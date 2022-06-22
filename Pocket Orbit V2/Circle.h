#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <cmath>

#include "PanZoom.h"

class Circle
{
private:

public:
	// Public Member Variables
	sf::CircleShape shape;

	// Constructor / Destructor
	Circle();
	Circle(float radius_in, sf::Vector2f position_in);
	~Circle();

	// Functions
	bool isMouseOnCircle(sf::RenderWindow& window_in) const;
	bool isMouseOnWorldCircle(sf::RenderWindow& window_in, PanZoom panZoom_in) const;
	float distanceTo(Circle circle_in) const;
	float distanceTo(sf::Vector2f position_in) const;
	bool isCollidedWith(Circle circle_in) const;
	bool isCollidedWith(float radius_in, sf::Vector2f position_in) const;
};