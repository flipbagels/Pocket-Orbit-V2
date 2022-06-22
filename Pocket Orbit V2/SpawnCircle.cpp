#include "SpawnCircle.h"


// Constructor / Destructor
SpawnCircle::SpawnCircle()
{
	this->obj.shape.setRadius(this->radius);
	this->obj.shape.setFillColor(sf::Color(0, 200, 255, 50));
	this->obj.shape.setOrigin(sf::Vector2f(this->radius, this->radius));
	this->obj.shape.setOutlineColor(sf::Color(0, 200, 255, 150));
	this->obj.shape.setOutlineThickness(5.0f);
}

SpawnCircle::~SpawnCircle()
{
}

// Functions
sf::Vector2f SpawnCircle::getPosition() const
{
	return this->position;
}

bool SpawnCircle::isMouseOnSpawn(sf::RenderWindow& window_in, PanZoom panZoom_in) const
{
	return (this->obj.isMouseOnWorldCircle(window_in, panZoom_in));
}

void SpawnCircle::updateSpawnCircle(sf::RenderWindow& window_in, PanZoom panZoom_in)
{
	if (this->isMouseOnSpawn(window_in, panZoom_in) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->pressed == false)
	{
		this->obj.shape.setFillColor(sf::Color(0, 200, 255, 25));
		this->obj.shape.setOutlineColor(sf::Color(0, 200, 255, 50));
		this->pressed = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->pressed == true)
	{
		this->obj.shape.setFillColor(sf::Color(0, 200, 255, 25));
		this->obj.shape.setOutlineColor(sf::Color(0, 200, 255, 50));
	}
	else
	{
		this->obj.shape.setFillColor(sf::Color(0, 200, 255, 50));
		this->obj.shape.setOutlineColor(sf::Color(0, 150, 255, 150));
		this->pressed = false;
	}
}

void SpawnCircle::decreaseSize()
{
	if (this->radius > 50.0f)
	{
		this->radius -= 10.0f;
	}
}

void SpawnCircle::resetSize()
{
	this->radius = 150.0f;
	this->obj.shape.setRadius(this->radius);
}

void SpawnCircle::respawn(sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y, float minDistFromSun_in)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> xDist(-offsetMax_x + this->radius + 200.0f, videoMode_in.width + offsetMax_x - this->radius - 200.0f);
	std::uniform_real_distribution<float> yDist(-offsetMax_y + this->radius + 200.0f, videoMode_in.height + offsetMax_y - this->radius - 200.0f);

	this->position.x = xDist(rng);
	if (this->position.x > (float(videoMode_in.width) / 2.0f) - minDistFromSun_in && this->position.x < (float(videoMode_in.width) / 2.0f) + minDistFromSun_in)
	{
		do
		{
			this->position.y = yDist(rng);
		} while (this->position.y > (float(videoMode_in.height) / 2) - minDistFromSun_in && this->position.y < (float(videoMode_in.height) / 2) + minDistFromSun_in);
	}
	else
	{
		this->position.y = yDist(rng);
	}

	this->obj.shape.setPosition(this->position);
}

void SpawnCircle::respawnToTarget(TargetCircle targetCircle_in)
{
	this->radius = targetCircle_in.getRadius();
	this->position = targetCircle_in.getPosition();
	this->obj.shape.setRadius(this->radius);
	this->obj.shape.setPosition(this->position);

}

SpawnCircle SpawnCircle::worldToScreen(PanZoom panZoom_in) const
{
	SpawnCircle projection = *this;

	projection.obj.shape.setPosition(panZoom_in.worldToScreen(this->position));
	projection.obj.shape.setRadius(this->radius * panZoom_in.getZoom());
	projection.obj.shape.setOrigin(this->radius * panZoom_in.getZoom(), this->radius * panZoom_in.getZoom());

	return projection;
}

void SpawnCircle::render(sf::RenderTarget& target)
{
	target.draw(this->obj.shape);
}