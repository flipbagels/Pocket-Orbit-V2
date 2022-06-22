#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Rectangle.h"
#include "Button.h"

class PauseUI
{
private:
	bool pause = false;
	Rectangle mask;

	sf::Vector2f levelSelectButtonPos;
	static constexpr float levelSelectButtonRadius = 60.0f;
	Button levelSelectButton;

	sf::Vector2f restartButtonPos;
	static constexpr float restartButtonRadius = 60.0f;
	Button restartButton;

	sf::Vector2f startButtonPos;
	static constexpr float startButtonRadius = 60.0f;
	Button startButton;


public:
	// Constructor / Destructor
	PauseUI();
	PauseUI(sf::VideoMode videoMode_in, std::map<std::string, sf::Texture>& textureMap_in);
	~PauseUI();

	// Functions
	void doPause();
	void unPause();
	bool isPaused() const;
	bool isMouseOnUI(sf::RenderWindow& window_in) const;
	void updateButtons(sf::RenderWindow& window_in);
	bool isLevelSelectPressed(sf::RenderWindow& window_in) const;
	bool isRestartPressed(sf::RenderWindow& window_in) const;
	bool isStartPressed(sf::RenderWindow& window_in) const;
	void render(sf::RenderTarget& target);
};