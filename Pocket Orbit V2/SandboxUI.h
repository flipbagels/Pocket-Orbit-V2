#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Button.h"

class SandboxUI
{
private:
	sf::Vector2f pauseButtonPos;
	static constexpr float pauseButtonRadius = 40.0f;
	Button pauseButton;

	std::vector<Button> planetArray;
	std::vector<Button> sataliteArray;

	bool ArraySwitch = false;
	int launchIndex = 0;


public:
	// Constructor / Destructor
	SandboxUI();
	SandboxUI(float width, float height, std::map<int, std::string> planetIndexMap_in, std::map<int, std::string> sataliteIndexMap_in, std::map<std::string, sf::Texture>& textureMap_in);
	~SandboxUI();

	// Functions
	bool getArraySwitch() const;
	int getLaunchIndex() const;
	void planetLaunch();
	void sataliteLaunch();
	bool isMouseOnUI(sf::RenderWindow& window_in) const;
	bool isPausePressed(sf::RenderWindow& window_in) const;
	bool isSelectionUIPressed(sf::RenderWindow& window_in) const;
	void updateLaunchIndex(sf::RenderWindow& window_in);
	void updateButtons(sf::RenderWindow& window_in);
	void render(sf::RenderTarget& target);
};