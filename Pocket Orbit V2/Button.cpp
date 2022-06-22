#include "Button.h"


// Constructor / Destructor
Button::Button()
{
}

Button::Button(float radius_in, sf::Vector2f position_in, sf::Texture& texture_in)
	:
	button(Circle(radius_in, position_in)),
	mask(Circle(radius_in, position_in)),
	outline(Circle(1.1f * radius_in, position_in))
{
	this->button.shape.setTexture(&texture_in);
	this->button.shape.setOutlineThickness(this->outlineThickness);
	this->button.shape.setOutlineColor(sf::Color(0, 150, 255, 0));

	this->mask.shape.setFillColor(sf::Color(0, 0, 0, 0));

	this->outline.shape.setFillColor(sf::Color(0, 0, 0, 0));
	this->outline.shape.setOutlineThickness(this->outlineThickness);
	this->outline.shape.setOutlineColor(sf::Color(0, 150, 255, 0));
}

Button::~Button()
{
}

// Functions
void Button::setSpacedOutlineColor(sf::Color color)
{
	this->outline.shape.setOutlineColor(color);
}

bool Button::isMouseOnbutton(sf::RenderWindow& window_in) const
{
	return (this->button.isMouseOnCircle(window_in));
}

bool Button::isPressed(sf::RenderWindow& window_in) const
{
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->button.isMouseOnCircle(window_in));
}

void Button::updateButtonMask(sf::RenderWindow& window_in)
{
	if (this->button.isMouseOnCircle(window_in))
	{
		this->mask.shape.setFillColor(sf::Color(0, 0, 0, 100));
	}
	else
	{
		this->mask.shape.setFillColor(sf::Color(0, 0, 0, 0));
	}
}

void Button::updateButtonSpacedOutline(sf::RenderWindow& window_in)
{
	if (this->button.isMouseOnCircle(window_in))
	{
		this->outline.shape.setOutlineColor(sf::Color(0, 150, 255, 255));
	}
	else
	{
		this->outline.shape.setOutlineColor(sf::Color(0, 150, 255, 0));
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->outline.shape);
	target.draw(this->button.shape);
	target.draw(this->mask.shape);
}