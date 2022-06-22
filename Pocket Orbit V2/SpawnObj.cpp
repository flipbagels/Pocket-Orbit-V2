#include "SpawnObj.h"


// Constructor / Destructor
SpawnObj::SpawnObj()
{
}

SpawnObj::SpawnObj(sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y, sf::Texture& texture_in)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> xDist(-offsetMax_x - 50.0f, float(videoMode_in.width) + offsetMax_x + 50.0f);
	std::uniform_real_distribution<float> yDist(-offsetMax_y - 50.0f, (float(videoMode_in.height) + offsetMax_y) / 2.0f);

	do
	{
		this->position.x = xDist(rng);
		this->position.y = yDist(rng);
	} while ((this->position.x > -offsetMax_x - this->radius && this->position.x < float(videoMode_in.width) + offsetMax_x + this->radius) && (this->position.y > -offsetMax_y - this->radius && this->position.y < float(videoMode_in.height) + offsetMax_y + this->radius));

	sf::Vector2f normal = (sf::Vector2f(float(videoMode_in.width) / 2.0f, float(videoMode_in.height) / 2.0f) - this->position) / this->obj.distanceTo(sf::Vector2f(float(videoMode_in.width) / 2.0f, float(videoMode_in.height) / 2.0f));
	this->velocity = normal * this->speed;

	this->obj.shape.setPosition(this->position);
	this->obj.shape.setRadius(this->radius);
	this->obj.shape.setOrigin(this->radius, this->radius);
	this->obj.shape.setTexture(&texture_in);
	this->obj.shape.setOutlineThickness(4.0f);
	this->obj.shape.setOutlineColor(sf::Color(0, 0, 0, 0));

	this->outline.shape.setPosition(this->position);
	this->outline.shape.setRadius(this->radius + this->outlineThickness);
	this->outline.shape.setOrigin(this->radius + this->outlineThickness, this->radius + this->outlineThickness);
	this->outline.shape.setFillColor(sf::Color(0, 0, 0, 0));
}

SpawnObj::~SpawnObj()
{
}

// Functions
float SpawnObj::getRadius() const
{
	return this->radius;
}

sf::Vector2f SpawnObj::getPosition() const
{
	return this->position;
}

void SpawnObj::updatePos()
{
	this->position += this->velocity;
	this->obj.shape.setPosition(this->position);
	this->outline.shape.setPosition(this->position);
}

void SpawnObj::updateOutline(sf::VideoMode videoMode_in)
{
	if (this->obj.distanceTo(sf::Vector2f(float(videoMode_in.width) / 2.0f, float(videoMode_in.height) / 2.0f)) < 255.0f)
	{
		this->outline.shape.setFillColor(sf::Color(255, 0, 0, 255 - this->obj.distanceTo(sf::Vector2f(float(videoMode_in.width) / 2.0f, float(videoMode_in.height) / 2.0f))));
	}
}

SpawnObj SpawnObj::worldToScreen(PanZoom panZoom_in) const
{
	SpawnObj projection = *this;

	projection.obj.shape.setPosition(panZoom_in.worldToScreen(this->position));
	projection.obj.shape.setRadius(this->radius * panZoom_in.getZoom());
	projection.obj.shape.setOrigin(this->radius * panZoom_in.getZoom(), this->radius * panZoom_in.getZoom());

	projection.outline.shape.setPosition(panZoom_in.worldToScreen(this->position));
	projection.outline.shape.setRadius((this->radius + this->outlineThickness) * panZoom_in.getZoom());
	projection.outline.shape.setOrigin((this->radius + this->outlineThickness) * panZoom_in.getZoom(), (this->radius + this->outlineThickness) * panZoom_in.getZoom());

	return projection;
}

void SpawnObj::render(sf::RenderTarget& target)
{
	target.draw(this->outline.shape);
	target.draw(this->obj.shape);
}