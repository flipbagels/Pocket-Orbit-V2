#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class PanZoom
{
private:
	bool offsetInhibit = false; // Used when panning
	bool targetInhibit = false; // Used during the change from a target to a sun object selection
	sf::Vector2f offset = sf::Vector2f(0.0f, 0.0f);
	float zoom = 1.0f;
	sf::Vector2f pickupOffset;
	sf::Vector2f releaseOffset;
	float zoomMax = 5.0;

public:
	// Level_1
	static constexpr float offsetMax1_x = 300.0f;
	static constexpr float offsetMax1_y = 200.0f;

	// Level_2
	static constexpr float offsetMax2_x = 690.0f;
	static constexpr float offsetMax2_y = 460.0f;

	// Level_3
	static constexpr float offsetMax3_x = -390.0f;
	static constexpr float offsetMax3_y = -260.0f;

	// Sandbox



public:
	// Constructor / Destructor
	PanZoom();
	~PanZoom();

	// Functions
	void setZoom(float zoom_in);
	float getZoom() const;
	void changePanUnlimited(sf::RenderWindow& window_in);
	void changePanLimited(sf::RenderWindow& window_in, sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y);
	void adjustPanTarget(sf::RenderWindow& window_in, sf::VideoMode videoMode_in, int orbitTargetID_in, sf::Vector2f targetPos_in);
	void changeZoomMouseUnlimited(sf::Event ev_in, sf::RenderWindow& window_in);
	void changeZoomMouseLimited(sf::Event ev_in, sf::RenderWindow& window_in, sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y);
	void changeZoomTarget(sf::Event ev_in, sf::RenderWindow& window_in, sf::Vector2f targetPos_in);
	sf::Vector2f screenToWorld(sf::Vector2f position_in) const;
	sf::Vector2f worldToScreen(sf::Vector2f position_in) const;
	void reset();
};