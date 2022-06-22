#include "Circle.h"


// Constructor / Destructor
Circle::Circle()
{
}

Circle::Circle(float radius_in, sf::Vector2f position_in)
{
	this->shape.setRadius(radius_in);
	this->shape.setOrigin(sf::Vector2f(radius_in, radius_in));
	this->shape.setPosition(position_in);
}

Circle::~Circle()
{
}

// Functions
bool Circle::isMouseOnCircle(sf::RenderWindow& window_in) const
{
	return (sqrt(pow(sf::Mouse::getPosition(window_in).x - this->shape.getPosition().x, 2) + pow(sf::Mouse::getPosition(window_in).y - this->shape.getPosition().y, 2)) <= this->shape.getRadius());
}

bool Circle::isMouseOnWorldCircle(sf::RenderWindow& window_in, PanZoom panZoom_in) const
{
	sf::Vector2f worldMousePos = panZoom_in.screenToWorld(sf::Vector2f(sf::Mouse::getPosition(window_in).x, sf::Mouse::getPosition(window_in).y));

	return (sqrt(pow(worldMousePos.x - this->shape.getPosition().x, 2) + pow(worldMousePos.y - this->shape.getPosition().y, 2)) <= this->shape.getRadius());
}

float Circle::distanceTo(Circle circle_in) const
{
	return sqrt(pow(this->shape.getPosition().x - circle_in.shape.getPosition().x, 2) + pow(this->shape.getPosition().y - circle_in.shape.getPosition().y, 2));
}

float Circle::distanceTo(sf::Vector2f position_in) const
{
	return sqrt(pow(this->shape.getPosition().x - position_in.x, 2) + pow(this->shape.getPosition().y - position_in.y, 2));
}

bool Circle::isCollidedWith(Circle circle_in) const
{
	return(this->distanceTo(circle_in) < this->shape.getRadius() + circle_in.shape.getRadius());
}

bool Circle::isCollidedWith(float radius_in, sf::Vector2f position_in) const
{
	return this->isCollidedWith(Circle(radius_in, position_in));
}