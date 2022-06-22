#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <random>

#include "Circle.h"
#include "TargetCircle.h"
#include "PanZoom.h"

class SpawnCircle
{
private:
	Circle obj;
	sf::Vector2f position;
	float radius = 150.0f;
	bool pressed = false;


public:
	// Constructor / Destructor
	SpawnCircle();
	~SpawnCircle();

	// Functions
	sf::Vector2f getPosition() const;
	bool isMouseOnSpawn(sf::RenderWindow& window_in, PanZoom panZoom_in) const;
	void updateSpawnCircle(sf::RenderWindow& window_in, PanZoom panZoom_in);
	void decreaseSize();
	void resetSize();
	void respawn(sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y, float minDistFromSun_in);
	void respawnToTarget(TargetCircle targetCircle_in);
	SpawnCircle worldToScreen(PanZoom panZoom_in) const;
	void render(sf::RenderTarget& target);
};