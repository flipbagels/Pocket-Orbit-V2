#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Circle.h"
#include "Rectangle.h"
#include "Button.h"
class Game;

class TitleScreen
{
private:
	// Text
	sf::Vector2f textPos;
	sf::Vector2f textSize = sf::Vector2f(600.0f, 400.0f);
	Rectangle text;

	// Earth, Trail, Orbit Values
	sf::Vector2f earthPos;
	static constexpr float earthRadius = 20.0f;
	static constexpr float earthSpeed = 6.0f;
	sf::Vector2f earthVel = earthSpeed * sf::Vector2f(1.0f, 0.0f);
	Circle earth;

	std::vector<Circle> earthRedTrail;
	static constexpr int earthRedTrailMax = 50;

	sf::Vector2f orbitCentre;
	static constexpr float orbitCentre_dx = -175.0f;
	static constexpr float orbitCentre_dy = 110.0f;
	static constexpr float orbitRadius = 65.0f;

	// Start Button
	sf::Vector2f startButtonPos;
	static constexpr float startButtonRadius = 40.0f;
	Button startButton;


public:
	// Constructor / Destructor
	TitleScreen();
	TitleScreen(float xPos_in, float yPos_in, sf::Texture& titleTextTexture_in, sf::Texture& earthTexture_in, sf::Texture& startButtonTexture_in);
	~TitleScreen();

	// Functions
	void reset();
	bool isMouseOnUI(sf::RenderWindow& window_in) const;
	bool isStartPressed(sf::RenderWindow& window_in) const;
	void updateButtons(sf::RenderWindow& window_in);
	void updateEarth();
	void updateEarthTrail();
	void render(sf::RenderTarget& target);
};