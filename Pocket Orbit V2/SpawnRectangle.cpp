#include "SpawnRectangle.h"


// Constructor / Destructor
SpawnRectangle::SpawnRectangle()
{
	this->obj.shape.setSize(this->size);
	this->obj.shape.setFillColor(sf::Color(0, 200, 255, 50));
	this->obj.shape.setOrigin(sf::Vector2f(this->size.x / 2, this->size.y / 2));
	this->obj.shape.setOutlineColor(sf::Color(0, 200, 255, 150));
	this->obj.shape.setOutlineThickness(5.0f);
}

SpawnRectangle::SpawnRectangle(sf::VideoMode videoMode_in, float offsetMax_y)
	:
	position(sf::Vector2f(float(videoMode_in.width) / 2.0f, float(videoMode_in.height) + offsetMax_y - (this->size.y / 2) - 5.0f))
{
	this->obj.shape.setPosition(this->position);
	this->obj.shape.setSize(this->size);
	this->obj.shape.setFillColor(sf::Color(0, 200, 255, 50));
	this->obj.shape.setOrigin(sf::Vector2f(this->size.x / 2, this->size.y / 2));
	this->obj.shape.setOutlineColor(sf::Color(0, 200, 255, 150));
	this->obj.shape.setOutlineThickness(5.0f);
}

SpawnRectangle::~SpawnRectangle()
{
}

// Functions
sf::Vector2f SpawnRectangle::getPosition() const
{
	return this->position;
}

bool SpawnRectangle::isMouseOnSpawn(sf::RenderWindow& window_in, PanZoom panZoom_in) const
{
	return (this->obj.isMouseOnWorldRectangle(window_in, panZoom_in));
}

void SpawnRectangle::updateSpawnRectangle(sf::RenderWindow& window_in, PanZoom panZoom_in)
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

void SpawnRectangle::reset(sf::VideoMode videoMode_in, float offsetMax_y)
{
	*this = SpawnRectangle(videoMode_in, offsetMax_y);
}

SpawnRectangle SpawnRectangle::worldToScreen(PanZoom panZoom_in) const
{
	SpawnRectangle projection = *this;

	projection.obj.shape.setPosition(panZoom_in.worldToScreen(this->position));
	projection.obj.shape.setSize(this->size * panZoom_in.getZoom());
	projection.obj.shape.setOrigin((this->size.x / 2) * panZoom_in.getZoom(), (this->size.y / 2) * panZoom_in.getZoom());

	return projection;
}

void SpawnRectangle::render(sf::RenderTarget& target)
{
	target.draw(this->obj.shape);
}