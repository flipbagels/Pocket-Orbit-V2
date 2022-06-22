#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <random>

#include "Circle.h"
#include "PanZoom.h"

class TargetCircle
{
private:

	Circle obj;
	sf::Vector2f position;
	float radius = 100.0f;

public:
	// Constructor / Destructor
	TargetCircle();
	~TargetCircle();

	// Functions
	float getRadius() const;
	sf::Vector2f getPosition() const;
	void decreaseSize();
	void resetSize();
	void respawn(sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y, float minDistFromSun_in, sf::Vector2f spawnPosition_in);
	TargetCircle worldToScreen(PanZoom panZoom_in) const;
	void render(sf::RenderTarget& target);
};