#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "PanZoom.h"
#include "SpawnCircle.h"
#include "SpawnRectangle.h"

#include <cmath>

class Line
{
private:
	sf::Vertex shape[2];
	sf::Vector2f A;
	sf::Vector2f B;
	bool readyForLaunch = false;
	bool updateLineInhibit = false;
	static constexpr float maxLength = 300.0f;

	// Private Functions
	void setVertexA(sf::Vector2f A_in);
	void setVertexB(sf::Vector2f B_in);

public:
	// Constructor / Destructor
	Line();
	~Line();

	// Functions
	sf::Vector2f getVertexA();
	sf::Vector2f getVertexB();
	bool isReadyForLaunch();
	void updateLine(sf::RenderWindow& window_in, SpawnCircle spawnCircle_in, PanZoom panZoom_in);
	void updateLine(sf::RenderWindow& window_in, SpawnRectangle spawnRectangle_in, PanZoom panZoom_in);
	void updateLine(sf::RenderWindow& window_in, PanZoom panZoom_in);
	float distanceToMouse(sf::RenderWindow& window_in) const;
	Line screenToWorld(PanZoom panZoom_in) const;
	void reset();
	void render(sf::RenderTarget& target);
};