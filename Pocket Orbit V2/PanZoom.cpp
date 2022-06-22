#include "PanZoom.h"


// Constructor/ Destructor
PanZoom::PanZoom()
{
}

PanZoom::~PanZoom()
{
}

// Functions
void PanZoom::setZoom(float zoom_in)
{
	this->zoom = zoom_in;
}

float PanZoom::getZoom() const
{
	return this->zoom;
}

void PanZoom::changePanUnlimited(sf::RenderWindow& window_in)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->offsetInhibit = false;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->offsetInhibit == false)
	{
		this->pickupOffset = sf::Vector2f(sf::Mouse::getPosition(window_in).x, sf::Mouse::getPosition(window_in).y);
		this->offsetInhibit = true;
	}
	else if (this->offsetInhibit == true)
	{
		this->releaseOffset = sf::Vector2f(sf::Mouse::getPosition(window_in).x, sf::Mouse::getPosition(window_in).y);
		this->offset += (this->releaseOffset - this->pickupOffset);

		this->pickupOffset = this->releaseOffset;
	}
}

void PanZoom::changePanLimited(sf::RenderWindow& window_in, sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y)
{
	// Panning
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->offsetInhibit = false;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->offsetInhibit == false)
	{
		this->pickupOffset = sf::Vector2f(sf::Mouse::getPosition(window_in).x, sf::Mouse::getPosition(window_in).y);
		this->offsetInhibit = true;
	}
	else if (this->offsetInhibit == true)
	{
		this->releaseOffset = sf::Vector2f(sf::Mouse::getPosition(window_in).x, sf::Mouse::getPosition(window_in).y);
		this->offset += (this->releaseOffset - this->pickupOffset);

		this->pickupOffset = this->releaseOffset;
	}

	// Checks boundaries and limits offset
	if ((-offsetMax_x * this->zoom) + this->offset.x > 0.0)
	{
		this->offset.x = offsetMax_x * this->zoom;
	}
	else if (((videoMode_in.width + offsetMax_x) * this->zoom) + this->offset.x < videoMode_in.width)
	{
		this->offset.x = videoMode_in.width - ((videoMode_in.width + offsetMax_x) * this->zoom);
	}
	if ((-offsetMax_y * this->zoom) + this->offset.y > 0.0)
	{
		this->offset.y = offsetMax_y * this->zoom;
	}
	else if (((videoMode_in.height + offsetMax_y) * zoom) + offset.y < videoMode_in.height)
	{
		this->offset.y = videoMode_in.height - ((videoMode_in.height + offsetMax_y) * this->zoom);
	}

}

void PanZoom::adjustPanTarget(sf::RenderWindow& window_in, sf::VideoMode videoMode_in, int orbitTargetID_in, sf::Vector2f targetPos_in)
{
	if (orbitTargetID_in != 0)
	{
		sf::Vector2f centre, targetOffset;
		centre = sf::Vector2f(float(videoMode_in.width) / 2.0f, float(videoMode_in.height) / 2.0f);
		targetOffset = centre - this->worldToScreen(targetPos_in);
		this->offset += targetOffset;
		this->targetInhibit = true;
	}
	else if (orbitTargetID_in == 0 && this->targetInhibit == true)
	{
		sf::Vector2f centre, targetOffset;
		centre = sf::Vector2f(float(videoMode_in.width) / 2.0f, float(videoMode_in.height) / 2.0f);
		targetOffset = centre - this->worldToScreen(targetPos_in);
		this->offset += targetOffset;
		this->targetInhibit = false;
	}
}

void PanZoom::changeZoomMouseUnlimited(sf::Event ev_in, sf::RenderWindow& window_in)
{
	sf::Vector2f zoomStartMousePos, zoomEndMousePos, oldScaleVector, newScaleVector;
	float oldZoom = this->zoom;

	this->zoom *= (1.0f + (float(ev_in.mouseWheel.delta) / 25));

	zoomStartMousePos = this->screenToWorld(sf::Vector2f(sf::Mouse::getPosition(window_in)));
	zoomEndMousePos = this->screenToWorld(sf::Vector2f(sf::Mouse::getPosition(window_in))) * oldZoom;
	oldScaleVector = zoomEndMousePos - zoomStartMousePos;

	zoomEndMousePos = this->screenToWorld(sf::Vector2f(sf::Mouse::getPosition(window_in))) * this->zoom;
	newScaleVector = zoomEndMousePos - zoomStartMousePos;

	this->offset += oldScaleVector - newScaleVector;

	if (this->zoom > this->zoomMax)
	{
		this->zoom = oldZoom;
		this->offset -= oldScaleVector - newScaleVector;
	}
}

void PanZoom::changeZoomMouseLimited(sf::Event ev_in, sf::RenderWindow& window_in, sf::VideoMode videoMode_in, float offsetMax_x, float offsetMax_y)
{
	// Zooming
	sf::Vector2f zoomStartMousePos, zoomEndMousePos, oldScaleVector, newScaleVector;
	float oldZoom = this->zoom;

	this->zoom *= (1.0f + (float(ev_in.mouseWheel.delta) / 25));

	zoomStartMousePos = this->screenToWorld(sf::Vector2f(sf::Mouse::getPosition(window_in)));
	zoomEndMousePos = this->screenToWorld(sf::Vector2f(sf::Mouse::getPosition(window_in))) * oldZoom;
	oldScaleVector = zoomEndMousePos - zoomStartMousePos;

	zoomEndMousePos = this->screenToWorld(sf::Vector2f(sf::Mouse::getPosition(window_in))) * this->zoom;
	newScaleVector = zoomEndMousePos - zoomStartMousePos;

	this->offset += oldScaleVector - newScaleVector;

	// Checks boundaries and limits zoom and offset
	if ((-offsetMax_x * this->zoom) + this->offset.x > 0.0 && ((videoMode_in.width + offsetMax_x) * this->zoom) + this->offset.x < videoMode_in.width)
	{
		this->zoom = videoMode_in.width / (videoMode_in.width + (2 * offsetMax_x));
	}
	if ((-offsetMax_y * this->zoom) + this->offset.y > 0.0 && ((videoMode_in.height + offsetMax_y) * this->zoom) + this->offset.y < videoMode_in.height)
	{
		this->zoom = videoMode_in.width / (videoMode_in.width + (2 * offsetMax_x));
	}
	if ((-offsetMax_x * this->zoom) + this->offset.x > 0.0)
	{
		this->offset.x = offsetMax_x * this->zoom;
	}
	else if (((videoMode_in.width + offsetMax_x) * this->zoom) + this->offset.x < videoMode_in.width)
	{
		this->offset.x = videoMode_in.width - ((videoMode_in.width + offsetMax_x) * this->zoom);
	}
	if ((-offsetMax_y * this->zoom) + this->offset.y > 0.0)
	{
		this->offset.y = offsetMax_y * this->zoom;
	}
	else if (((videoMode_in.height + offsetMax_y) * this->zoom) + this->offset.y < videoMode_in.height)
	{
		this->offset.y = videoMode_in.height - ((videoMode_in.height + offsetMax_y) * this->zoom);
	}

	if (this->zoom > this->zoomMax)
	{
		this->zoom = oldZoom;
		this->offset -= oldScaleVector - newScaleVector;
	}
}

void PanZoom::changeZoomTarget(sf::Event ev_in, sf::RenderWindow& window_in, sf::Vector2f targetPos_in)
{
	sf::Vector2f zoomStartMousePos, zoomEndMousePos, oldScaleVector, newScaleVector;
	float oldZoom = this->zoom;

	this->zoom *= (1.0f + (float(ev_in.mouseWheel.delta) / 25));

	zoomStartMousePos = targetPos_in;
	zoomEndMousePos = targetPos_in * oldZoom;
	oldScaleVector = zoomEndMousePos - zoomStartMousePos;

	zoomEndMousePos = targetPos_in * this->zoom;
	newScaleVector = zoomEndMousePos - zoomStartMousePos;

	this->offset += oldScaleVector - newScaleVector;

	if (this->zoom > this->zoomMax)
	{
		this->zoom = oldZoom;
		this->offset -= oldScaleVector - newScaleVector;
	}
}

sf::Vector2f PanZoom::screenToWorld(sf::Vector2f position_in) const
{
	return (position_in - this->offset) / this->zoom;
}

sf::Vector2f PanZoom::worldToScreen(sf::Vector2f position_in) const
{
	return ((position_in * this->zoom) + this->offset);
}

void PanZoom::reset()
{
	this->offset = sf::Vector2f(0.0f, 0.0f);
	this->zoom = 1.0f;
}