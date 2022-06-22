#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Circle.h"
#include "Line.h"
#include "TargetCircle.h"
#include "SpawnObj.h"
#include "FrameTimer.h"
#include "PanZoom.h"
#include "Button.h"

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

class SpaceObj
{
private:
	// Comet
	Circle obj;
	Circle outline;
	static constexpr float outlineThickness = 7.0f;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f forceVector;
	float forceScalar;
	float radius;
	float mass;
	std::string type;
	int targetID;

	// Trail
	std::vector<Circle> redTrail;
	static constexpr int cometRedTrailMax = 8;
	static constexpr int weaponRedTrailMax = 7;

	// Calculation Constants
	static constexpr float massConstant = 10.0f;
	static constexpr float forceScalarConstant = 90.0f;
	static constexpr float velocityConstant = 0.018f;

public:
	// Constructor / Destructor
	SpaceObj();
	SpaceObj(sf::Vector2f pos, sf::Vector2f vel, float radius_in, std::string type_in, int targetID_in, sf::Texture& texture_in);
	SpaceObj(Line launchLine_in, float radius_in, std::string type_in, int targetID_in, sf::Texture& texture_in);
	~SpaceObj();

	// Functions
	sf::Vector2f getPosition();
	void setTargetID(int newTargetID);
	int getTargetID();
	std::string getType();
	void setOutlineColor(sf::Color colour_in);
	void updateOutlineColor(sf::RenderWindow& window_in, PanZoom panZoom_in);
	bool isPressed(sf::RenderWindow& window_in, PanZoom panZoom_in) const;
	void updatePos(std::vector<SpaceObj> SpaceObjArray_in); // Never call function on Sun (object 0 in array)
	bool isCollidedWith(SpaceObj spaceObj_in) const;
	void updateCollision(SpaceObj& spaceObj_in);
	bool isCollidedWithSun(SpaceObj sun_in) const;
	void updateSunCollision(SpaceObj sun_in);
	bool isCollidedWith(TargetCircle targetCircle_in) const;
	bool isCollidedWith(SpawnObj spawnObj_in) const;
	void updateRedTrail(SpaceObj sun_in);
	SpaceObj worldToScreen(PanZoom panZoom_in) const;
	void render(sf::RenderTarget& target);
};