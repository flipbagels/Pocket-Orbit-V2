#include "Score.h"


// Constructor / Destructor
Score::Score()
{
}

Score::Score(sf::Font& font_in, sf::VideoMode videoMode_in)
	:
	position(float(videoMode_in.width / 2), 40.0f)
{
	this->scoreText.setFont(font_in);
	this->scoreText.setCharacterSize(50);
	this->scoreText.setStyle(sf::Text::Bold);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setPosition(this->position);
}

Score::~Score()
{
}

// Functions
void Score::increaseScoreCounter()
{
	this->scoreCounter.increase();
}

int Score::getScoreCounter() const
{
	return (this->scoreCounter.getCount());
}

void Score::resetScoreCounter()
{
	this->scoreCounter.reset();
}

void Score::render(sf::RenderTarget& target)
{
	std::ostringstream ss;
	ss << this->scoreCounter.getCount();

	this->scoreText.setString(ss.str());

	target.draw(this->scoreText);
}