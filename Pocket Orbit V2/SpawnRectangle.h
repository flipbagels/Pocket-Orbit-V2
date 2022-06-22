#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Rectangle.h"
#include "PanZoom.h"

class SpawnRectangle
{
private:
	Rectangle obj;
	sf::Vector2f size = sf::Vector2f(450.0f, 100.0f);
	sf::Vector2f position;
	bool pressed = false;

public:
	// Constructor / Destructor
	SpawnRectangle();
	SpawnRectangle(sf::VideoMode videoMode_in, float offsetMax_y);
	~SpawnRectangle();

	// Functions
	sf::Vector2f getPosition() const;
	bool isMouseOnSpawn(sf::RenderWindow& window_in, PanZoom panZoom_in) const;
	void updateSpawnRectangle(sf::RenderWindow& window_in, PanZoom panZoom_in);
	void reset(sf::VideoMode videoMode_in, float offsetMax_y);
	SpawnRectangle worldToScreen(PanZoom panZoom_in) const;
	void render(sf::RenderTarget& target);
};