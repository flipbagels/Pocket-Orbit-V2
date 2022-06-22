#include "TargetCircle.h"


// Constructor / Destructor
TargetCircle::TargetCircle()
{
	this->obj.shape.setRadius(this->radius);
	this->obj.shape.setFillColor(sf::Color(0, 255, 100, 50));
	this->obj.shape.setOrigin(sf::Vector2f(this->radius, this->radius));
	this->obj.shape.setOutlineColor(sf::Color(0, 255, 100, 150));
	this->obj.shape.setOutlineThickness(5.0f);
}

TargetCircle::~TargetCircle()
{
}

// Functions
float TargetCircle::getRadius() const
{
	return this->radius;
}

sf::Vector2f TargetCircle::getPosition() const
{
	return this->position;
}

void TargetCircle::decreaseSize()
{
	if (this->radius > 50.0f)
	{
		this->radius -= 10.0f;
	}
}

void TargetCircle::resetSize()
{
	this->radius = 150.0f;
}

void TargetCircle::respawn(sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y, float minDistFromSun_in, sf::Vector2f spawnPosition_in)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> xDist(-offsetMax_x + this->radius + 200.0f, videoMode_in.width + offsetMax_x - this->radius - 200.0f);
	std::uniform_real_distribution<float> yDist(-offsetMax_y + this->radius + 200.0f, videoMode_in.height + offsetMax_y - this->radius - 200.0f);

	do
	{
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
	} while (this->obj.distanceTo(spawnPosition_in) < 400.0f);
}

TargetCircle TargetCircle::worldToScreen(PanZoom panZoom_in) const
{
	TargetCircle projection = *this;

	projection.obj.shape.setPosition(panZoom_in.worldToScreen(this->position));
	projection.obj.shape.setRadius(this->radius * panZoom_in.getZoom());
	projection.obj.shape.setOrigin(this->radius * panZoom_in.getZoom(), this->radius * panZoom_in.getZoom());

	return projection;
}

void TargetCircle::render(sf::RenderTarget& target)
{
	target.draw(this->obj.shape);
}