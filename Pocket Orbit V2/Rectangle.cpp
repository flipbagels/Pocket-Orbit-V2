#include "Rectangle.h"

// Constructor / Destructor
Rectangle::Rectangle()
{
}

Rectangle::Rectangle(sf::Vector2f size_in, sf::Vector2f position_in)
{
	this->shape.setSize(size_in);
	this->shape.setOrigin(this->shape.getSize().x / 2, this->shape.getSize().y / 2);
	this->shape.setPosition(position_in);
}

Rectangle::~Rectangle()
{
}

// Functions
bool Rectangle::isMouseOnRectangle(sf::RenderWindow& window_in) const
{
	return (sf::Mouse::getPosition(window_in).x >= this->shape.getPosition().x - (this->shape.getSize().x / 2)
		&& sf::Mouse::getPosition(window_in).x <= this->shape.getPosition().x + (this->shape.getSize().x / 2)
		&& sf::Mouse::getPosition(window_in).y >= this->shape.getPosition().y - (this->shape.getSize().y / 2)
		&& sf::Mouse::getPosition(window_in).y <= this->shape.getPosition().y + (this->shape.getSize().y / 2));
}

bool Rectangle::isMouseOnWorldRectangle(sf::RenderWindow& window_in, PanZoom panZoom_in) const
{
	sf::Vector2f worldMousePos = panZoom_in.screenToWorld(sf::Vector2f(sf::Mouse::getPosition(window_in).x, sf::Mouse::getPosition(window_in).y));

	return (worldMousePos.x >= this->shape.getPosition().x - (this->shape.getSize().x / 2)
		&& worldMousePos.x <= this->shape.getPosition().x + (this->shape.getSize().x / 2)
		&& worldMousePos.y >= this->shape.getPosition().y - (this->shape.getSize().y / 2)
		&& worldMousePos.y <= this->shape.getPosition().y + (this->shape.getSize().y / 2));
}