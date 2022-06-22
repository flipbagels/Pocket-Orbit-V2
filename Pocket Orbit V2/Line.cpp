#include "Line.h"


// Constructor / Destructor
Line::Line()
{
}

Line::~Line()
{
}

// Functions
void Line::setVertexA(sf::Vector2f A_in)
{
	this->A = A_in;
	this->shape[0] = A_in;
}

void Line::setVertexB(sf::Vector2f B_in)
{
	this->B = B_in;
	this->shape[1] = B_in;
}

sf::Vector2f Line::getVertexA()
{
	return this->A;
}

sf::Vector2f Line::getVertexB()
{
	return this->B;
}

bool Line::isReadyForLaunch()
{
	return this->readyForLaunch;
}

void Line::updateLine(sf::RenderWindow& window_in, SpawnCircle spawnCircle_in, PanZoom panZoom_in)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == false && this->readyForLaunch == false && spawnCircle_in.isMouseOnSpawn(window_in, panZoom_in))
	{
		this->setVertexA(sf::Vector2f(sf::Mouse::getPosition(window_in)));
		this->setVertexB(sf::Vector2f(sf::Mouse::getPosition(window_in)));
		this->updateLineInhibit = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == true && this->readyForLaunch == false && this->distanceToMouse(window_in) < this->maxLength * panZoom_in.getZoom())
	{
		this->setVertexB(sf::Vector2f(sf::Mouse::getPosition(window_in)));
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == true && this->readyForLaunch == false && this->distanceToMouse(window_in) >= this->maxLength * panZoom_in.getZoom())
	{
		sf::Vector2f unitVector = (sf::Vector2f(sf::Mouse::getPosition(window_in).x, sf::Mouse::getPosition(window_in).y) - this->A) / this->distanceToMouse(window_in);
		this->setVertexB(this->A + (this->maxLength * unitVector * panZoom_in.getZoom()));
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == true && this->readyForLaunch == false)
	{
		this->readyForLaunch = true;
	}
	else
	{
		this->updateLineInhibit = false;
		this->readyForLaunch = false;
		this->reset();
	}
}

void Line::updateLine(sf::RenderWindow& window_in, SpawnRectangle spawnRectangle_in, PanZoom panZoom_in)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == false && this->readyForLaunch == false && spawnRectangle_in.isMouseOnSpawn(window_in, panZoom_in))
	{
		this->setVertexA(sf::Vector2f(sf::Mouse::getPosition(window_in)));
		this->setVertexB(sf::Vector2f(sf::Mouse::getPosition(window_in)));
		this->updateLineInhibit = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == true && this->readyForLaunch == false && this->distanceToMouse(window_in) < this->maxLength * panZoom_in.getZoom())
	{
		this->setVertexB(sf::Vector2f(sf::Mouse::getPosition(window_in)));
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == true && this->readyForLaunch == false && this->distanceToMouse(window_in) >= this->maxLength * panZoom_in.getZoom())
	{
		sf::Vector2f unitVector = (sf::Vector2f(sf::Mouse::getPosition(window_in).x, sf::Mouse::getPosition(window_in).y) - this->A) / this->distanceToMouse(window_in);
		this->setVertexB(this->A + (this->maxLength * unitVector * panZoom_in.getZoom()));
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == true && this->readyForLaunch == false)
	{
		this->readyForLaunch = true;
	}
	else
	{
		this->updateLineInhibit = false;
		this->readyForLaunch = false;
		this->reset();
	}
}

void Line::updateLine(sf::RenderWindow& window_in, PanZoom panZoom_in)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == false && this->readyForLaunch == false)
	{
		this->setVertexA(sf::Vector2f(sf::Mouse::getPosition(window_in)));
		this->setVertexB(sf::Vector2f(sf::Mouse::getPosition(window_in)));
		this->updateLineInhibit = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == true && this->readyForLaunch == false && this->distanceToMouse(window_in) < this->maxLength * panZoom_in.getZoom())
	{
		this->setVertexB(sf::Vector2f(sf::Mouse::getPosition(window_in)));
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == true && this->readyForLaunch == false && this->distanceToMouse(window_in) >= this->maxLength * panZoom_in.getZoom())
	{
		sf::Vector2f unitVector = (sf::Vector2f(sf::Mouse::getPosition(window_in).x, sf::Mouse::getPosition(window_in).y) - this->A) / this->distanceToMouse(window_in);
		this->setVertexB(this->A + (this->maxLength * unitVector * panZoom_in.getZoom()));
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->updateLineInhibit == true && this->readyForLaunch == false)
	{
		this->readyForLaunch = true;
	}
	else
	{
		this->updateLineInhibit = false;
		this->readyForLaunch = false;
		this->reset();
	}
}

float Line::distanceToMouse(sf::RenderWindow& window_in) const
{
	return (sqrt(pow(this->A.x - float(sf::Mouse::getPosition(window_in).x), 2) + pow(this->A.y - float(sf::Mouse::getPosition(window_in).y), 2)));
}

Line Line::screenToWorld(PanZoom panZoom_in) const
{
	Line projection = *this;

	projection.setVertexA(panZoom_in.screenToWorld(this->A));
	projection.setVertexB(panZoom_in.screenToWorld(this->B));

	return projection;
}

void Line::reset()
{
	this->setVertexA(sf::Vector2f(0.0f, 0.0f));
	this->setVertexB(sf::Vector2f(0.0f, 0.0f));
	this->readyForLaunch = false;
	this->updateLineInhibit = false;
}

void Line::render(sf::RenderTarget& target)
{
	target.draw(this->shape, 2, sf::Lines);
}