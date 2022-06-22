#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Circle.h"
#include "PanZoom.h"

#include <random>

class SpawnObj
{
private:
	Circle obj;
	Circle outline;
	static constexpr float outlineThickness = 2.0f;
	float radius = 7.0f;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed = 2.0f;


public:
	// Constructor / Destructor
	SpawnObj();
	SpawnObj(sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y, sf::Texture& texture_in);
	~SpawnObj();

	// Functions
	float getRadius() const;
	sf::Vector2f getPosition() const;
	void updatePos();
	void updateOutline(sf::VideoMode videoMode_in);
	SpawnObj worldToScreen(PanZoom panZoom_in) const;
	void render(sf::RenderTarget& target);
};