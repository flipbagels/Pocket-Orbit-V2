#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Counter.h"

#include <sstream>

class Score
{
private:
	Counter scoreCounter;
	sf::Text scoreText;
	sf::Vector2f position;
	static constexpr int size = 50;


public:
	// Constructor / Destructor
	Score();
	Score(sf::Font& font_in, sf::VideoMode videoMode_in);
	~Score();

	// Functions
	void increaseScoreCounter();
	int getScoreCounter() const;
	void resetScoreCounter();
	void render(sf::RenderTarget& target);
};