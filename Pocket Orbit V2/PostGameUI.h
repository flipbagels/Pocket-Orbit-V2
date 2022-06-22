#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


#include "Rectangle.h"
#include "Button.h"
#include "Score.h"

class PostGameUI
{
private:
	bool postGameBool = false;
	Rectangle mask;

	sf::Vector2f postGameTextPos;
	sf::Text postGameText;

	sf::Vector2f levelSelectButtonPos;
	static constexpr float levelSelectButtonRadius = 60.0f;
	Button levelSelectButton;

	sf::Vector2f restartButtonPos;
	static constexpr float restartButtonRadius = 60.0f;
	Button restartButton;


public:
	// Constructor / Destructor
	PostGameUI();
	PostGameUI(sf::Font& font_in, sf::VideoMode videoMode_in, std::map<std::string, sf::Texture>& textureMap_in);
	~PostGameUI();

	// Functions
	void beginPostGame();
	void endPostGame();
	bool isPostGameActive() const;
	bool isMouseOnUI(sf::RenderWindow& window_in) const;
	void updateButtons(sf::RenderWindow& window_in);
	bool isLevelSelectPressed(sf::RenderWindow& window_in) const;
	bool isRestartPressed(sf::RenderWindow& window_in) const;
	void render(sf::RenderTarget& target, Score score_in);
};