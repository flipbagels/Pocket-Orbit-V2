#include "SpaceObj.h"


// Constructor / Destructor
SpaceObj::SpaceObj()
{

}

SpaceObj::SpaceObj(sf::Vector2f pos, sf::Vector2f vel, float radius_in, std::string type_in, int targetID_in, sf::Texture& texture_in)
	:
	position(pos),
	velocity(vel),
	radius(radius_in),
	mass(this->massConstant* (this->radius)), // In real life should be cubed
	type(type_in),
	targetID(targetID_in)
{
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

SpaceObj::SpaceObj(Line launchLine_in, float radius_in, std::string type_in, int targetID_in, sf::Texture& texture_in)
	:
	position(launchLine_in.getVertexA()),
	velocity(powf(radius_in, 0.1)* this->velocityConstant* (launchLine_in.getVertexA() - launchLine_in.getVertexB())), // Makes velocity proportional to sqrt of radius
	radius(radius_in),
	mass(this->massConstant* (this->radius)), // In real life should be cubed
	type(type_in),
	targetID(targetID_in)
{
	this->obj.shape.setPosition(this->position);
	this->obj.shape.setRadius(this->radius);
	this->obj.shape.setOrigin(radius_in, radius_in);
	this->obj.shape.setTexture(&texture_in);
	this->obj.shape.setOutlineThickness(4.0f);
	this->obj.shape.setOutlineColor(sf::Color(0, 0, 0, 0));

	this->outline.shape.setPosition(this->position);
	this->outline.shape.setRadius(this->radius + this->outlineThickness);
	this->outline.shape.setOrigin(this->radius + this->outlineThickness, this->radius + this->outlineThickness);
	this->outline.shape.setFillColor(sf::Color(0, 0, 0, 0));
}

SpaceObj::~SpaceObj()
{
}

// Functions
sf::Vector2f SpaceObj::getPosition()
{
	return this->obj.shape.getPosition();
}

void SpaceObj::setTargetID(int newTargetID)
{
	this->targetID = newTargetID;
}

int SpaceObj::getTargetID()
{
	return this->targetID;
}

std::string SpaceObj::getType()
{
	return this->type;
}

void SpaceObj::setOutlineColor(sf::Color colour_in)
{
	this->outline.shape.setFillColor(colour_in);
}

void SpaceObj::updateOutlineColor(sf::RenderWindow& window_in, PanZoom panZoom_in)
{
	if (this->obj.isMouseOnWorldCircle(window_in, panZoom_in))
	{
		this->outline.shape.setFillColor(sf::Color(0, 150, 255, 255));
	}
	else
	{
		this->outline.shape.setFillColor(sf::Color(0, 150, 255, 0));
	}
}

bool SpaceObj::isPressed(sf::RenderWindow& window_in, PanZoom panZoom_in) const
{
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->obj.isMouseOnWorldCircle(window_in, panZoom_in));
}

void SpaceObj::updatePos(std::vector<SpaceObj> SpaceObjArray_in)
{
	this->forceScalar = (this->forceScalarConstant * this->mass) / pow((sqrt(pow(this->position.x - SpaceObjArray_in[this->targetID].position.x, 2) + pow(this->position.y - SpaceObjArray_in[this->targetID].position.y, 2))), 3);
	this->forceVector = (SpaceObjArray_in[this->targetID].position - this->position) * this->forceScalar;

	if (this->targetID == 0)
	{
		this->velocity += this->forceVector;
		this->position += this->velocity;
		this->obj.shape.setPosition(this->position);
		if (type == "Weapon")
		{
			float angle = (180 / M_PI) * acos((this->velocity.y) / sqrt((this->velocity.x * this->velocity.x) + (this->velocity.y * this->velocity.y)));
			if (this->velocity.x >= 0.0f)
			{
				this->obj.shape.setRotation(-angle + 180.0f);
			}
			else
			{
				this->obj.shape.setRotation(angle + 180.0f);
			}
			this->obj.shape.setScale(3.0f, 3.0f);
		}
	}
	else
	{
		this->velocity += this->forceVector;
		this->position += (this->velocity + SpaceObjArray_in[this->targetID].velocity);
		this->obj.shape.setPosition(this->position);
	}
}

bool SpaceObj::isCollidedWith(SpaceObj spaceObj_in) const
{
	return (obj.isCollidedWith(spaceObj_in.obj));
}

void SpaceObj::updateCollision(SpaceObj& spaceObj_in)
{
	float distance, halfOverlap;
	sf::Vector2f normalVector, positionDifference, velocityDifference;

	distance = this->obj.distanceTo(spaceObj_in.obj);
	halfOverlap = ((this->radius + spaceObj_in.radius - distance) / 2);
	normalVector = (this->position - spaceObj_in.position) / distance;
	positionDifference = this->position - spaceObj_in.position;
	velocityDifference = this->velocity - spaceObj_in.velocity;

	this->position += (halfOverlap * normalVector);
	this->velocity -= (2 * spaceObj_in.mass / (this->mass + spaceObj_in.mass)) * (((velocityDifference.x * positionDifference.x) + (velocityDifference.y * positionDifference.y)) / (distance * distance)) * positionDifference;

	spaceObj_in.position -= (halfOverlap * normalVector);
	spaceObj_in.velocity -= (2 * this->mass / (this->mass + spaceObj_in.mass)) * ((((-velocityDifference.x) * (-positionDifference.x)) + ((-velocityDifference.y) * (-positionDifference.y))) / (distance * distance)) * (-positionDifference);
}

bool SpaceObj::isCollidedWithSun(SpaceObj sun_in) const
{
	return (sqrt(pow(this->position.x - sun_in.position.x, 2) + pow(this->position.y - sun_in.position.y, 2)) < this->radius + (0.9f * sun_in.radius));
}

void SpaceObj::updateSunCollision(SpaceObj sun_in)
{
}

bool SpaceObj::isCollidedWith(TargetCircle targetCircle_in) const
{
	return (obj.isCollidedWith(targetCircle_in.getRadius(), targetCircle_in.getPosition()));
}

bool SpaceObj::isCollidedWith(SpawnObj spawnObj_in) const
{
	return (obj.isCollidedWith(spawnObj_in.getRadius(), spawnObj_in.getPosition()));
}

void SpaceObj::updateRedTrail(SpaceObj sun_in)
{
	if (this->type == "Comet")
	{
		if (this->obj.distanceTo(sun_in.obj) < 4.0f * (this->radius + sun_in.radius) && this->redTrail.size() < this->cometRedTrailMax)
		{
			this->redTrail.push_back(Circle(this->radius, this->position));
		}
		else if (this->obj.distanceTo(sun_in.obj) < 4.0f * (this->radius + sun_in.radius) && this->redTrail.size() >= this->cometRedTrailMax)
		{
			this->redTrail.erase(this->redTrail.begin());
			this->redTrail.push_back(Circle(this->radius, this->position));
		}
		else if (this->obj.distanceTo(sun_in.obj) >= 4.0f * (this->radius + sun_in.radius) && this->redTrail.size() > 1)
		{
			this->redTrail.erase(this->redTrail.begin());
			this->redTrail.erase(this->redTrail.begin());
			this->redTrail.push_back(Circle(this->radius, this->position));
		}
		else if (this->obj.distanceTo(sun_in.obj) >= 4.0f * (this->radius + sun_in.radius) && this->redTrail.size() == 1)
		{
			this->redTrail.erase(this->redTrail.begin());
		}
		else
		{
		}
		for (int i = 0; i < this->redTrail.size(); i++)
		{
			this->redTrail[i].shape.setFillColor(sf::Color(255, 0, 0, 255 / (this->redTrail.size() - i)));
		}
	}
	else if (this->type == "Weapon")
	{
		if (this->redTrail.size() < this->weaponRedTrailMax)
		{
			this->redTrail.push_back(Circle(this->radius, this->position));
		}
		else if (this->redTrail.size() >= this->weaponRedTrailMax)
		{
			this->redTrail.erase(this->redTrail.begin());
			this->redTrail.push_back(Circle(this->radius, this->position));
		}
		else if (this->redTrail.size() > 1)
		{
			this->redTrail.erase(this->redTrail.begin());
			this->redTrail.erase(this->redTrail.begin());
			this->redTrail.push_back(Circle(this->radius, this->position));
		}
		else if (this->redTrail.size() == 1)
		{
			this->redTrail.erase(this->redTrail.begin());
		}
		else
		{
		}
		for (int i = 0; i < this->redTrail.size(); i++)
		{
			this->redTrail[i].shape.setFillColor(sf::Color(255, 0, 0, 255 / (this->redTrail.size() - i)));
		}
	}
}

SpaceObj SpaceObj::worldToScreen(PanZoom panZoom_in) const
{
	SpaceObj projection = *this;

	projection.obj.shape.setPosition(panZoom_in.worldToScreen(this->position));
	projection.obj.shape.setRadius(this->radius * panZoom_in.getZoom());
	projection.obj.shape.setOrigin(this->radius * panZoom_in.getZoom(), this->radius * panZoom_in.getZoom());

	projection.outline.shape.setPosition(panZoom_in.worldToScreen(this->position));
	projection.outline.shape.setRadius((this->radius + this->outlineThickness) * panZoom_in.getZoom());
	projection.outline.shape.setOrigin((this->radius + this->outlineThickness) * panZoom_in.getZoom(), (this->radius + this->outlineThickness) * panZoom_in.getZoom());

	if (this->type == "Comet" || this->type == "Weapon")
	{
		for (int i = 0; i < projection.redTrail.size(); i++)
		{
			projection.redTrail[i].shape.setPosition(panZoom_in.worldToScreen(this->redTrail[i].shape.getPosition()));
			projection.redTrail[i].shape.setRadius(this->redTrail[i].shape.getRadius() * panZoom_in.getZoom());
			projection.redTrail[i].shape.setOrigin(this->redTrail[i].shape.getRadius() * panZoom_in.getZoom(), this->redTrail[i].shape.getRadius() * panZoom_in.getZoom());
		}
	}

	return projection;
}

void SpaceObj::render(sf::RenderTarget& target)
{
	if (this->type == "Comet" || this->type == "Weapon")
	{
		for (int i = 0; i < this->redTrail.size(); i++)
		{
			target.draw(this->redTrail[i].shape);
		}
	}
	target.draw(this->outline.shape);
	target.draw(this->obj.shape);
}