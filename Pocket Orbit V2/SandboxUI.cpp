#include "SandboxUI.h"


// Constructor / Destructor
SandboxUI::SandboxUI()
{
}

SandboxUI::SandboxUI(float width, float height, std::map<int, std::string> planetIndexMap_in, std::map<int, std::string> sataliteIndexMap_in, std::map<std::string, sf::Texture>& textureMap_in)
	:
	pauseButtonPos(sf::Vector2f(60.0f, 60.0f)),
	pauseButton(this->pauseButtonRadius, this->pauseButtonPos, textureMap_in["PauseButton"])
{
	for (int i = 0; i < planetIndexMap_in.size(); i++)
	{
		this->planetArray.push_back(Button(40.0f, sf::Vector2f(0.96 * width, (0.93 * height) - (100.0 * i)), textureMap_in[planetIndexMap_in[i]]));
	}

	for (int i = 0; i < sataliteIndexMap_in.size(); i++)
	{
		this->sataliteArray.push_back(Button(40.0f, sf::Vector2f(0.96 * width, (0.93 * height) - (100.0 * i)), textureMap_in[sataliteIndexMap_in[i]]));
	}

}

SandboxUI::~SandboxUI()
{
}

// Functions
bool SandboxUI::getArraySwitch() const
{
	return this->ArraySwitch;
}

int SandboxUI::getLaunchIndex() const
{
	return this->launchIndex;
}

void SandboxUI::planetLaunch()
{
	this->ArraySwitch = false;
	this->launchIndex = 0;
}

void SandboxUI::sataliteLaunch()
{
	this->ArraySwitch = true;
	this->launchIndex = 0;
}

bool SandboxUI::isMouseOnUI(sf::RenderWindow& window_in) const
{
	bool output = false;

	if (!this->ArraySwitch)
	{
		for (int i = 0; i < this->planetArray.size(); i++)
		{
			if (output == false)
			{
				output = this->planetArray[i].isMouseOnbutton(window_in);
			}
		}
	}
	else if (this->ArraySwitch)
	{
		for (int i = 0; i < this->sataliteArray.size(); i++)
		{
			if (output == false)
			{
				output = this->sataliteArray[i].isMouseOnbutton(window_in);
			}
		}
	}

	return (this->pauseButton.isMouseOnbutton(window_in) || output);
}

bool SandboxUI::isPausePressed(sf::RenderWindow& window_in) const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || this->pauseButton.isPressed(window_in));
}

bool SandboxUI::isSelectionUIPressed(sf::RenderWindow& window_in) const
{
	bool output = false;

	if (!this->ArraySwitch)
	{
		for (int i = 0; i < this->planetArray.size(); i++)
		{
			if (output == false)
			{
				output = this->planetArray[i].isPressed(window_in);
			}
		}
	}
	else if (this->ArraySwitch)
	{
		for (int i = 0; i < this->sataliteArray.size(); i++)
		{
			if (output == false)
			{
				output = this->sataliteArray[i].isPressed(window_in);
			}
		}
	}

	return output;
}

void SandboxUI::updateLaunchIndex(sf::RenderWindow& window_in)
{
	if (this->isSelectionUIPressed(window_in))
	{
		if (!this->ArraySwitch)
		{
			for (int i = 0; i < this->planetArray.size(); i++)
			{
				if (this->planetArray[i].isPressed(window_in))
				{
					this->launchIndex = i;
				}
			}
		}
		else if (this->ArraySwitch)
		{
			for (int i = 0; i < this->sataliteArray.size(); i++)
			{
				if (this->sataliteArray[i].isPressed(window_in))
				{
					this->launchIndex = i;
				}
			}
		}
	}
}

void SandboxUI::updateButtons(sf::RenderWindow& window_in)
{
	this->pauseButton.updateButtonMask(window_in);

	if (!this->ArraySwitch)
	{
		for (int i = 0; i < this->planetArray.size(); i++)
		{
			if (this->launchIndex == i)
			{
				this->planetArray[i].setSpacedOutlineColor(sf::Color(0, 255, 0, 255));
			}
			else
			{
				this->planetArray[i].updateButtonSpacedOutline(window_in);
			}
		}
	}
	else if (this->ArraySwitch)
	{
		for (int i = 0; i < this->sataliteArray.size(); i++)
		{
			if (this->launchIndex == i)
			{
				this->sataliteArray[i].setSpacedOutlineColor(sf::Color(0, 255, 0, 255));
			}
			else
			{
				this->sataliteArray[i].updateButtonSpacedOutline(window_in);
			}
		}
	}
}

void SandboxUI::render(sf::RenderTarget& target)
{
	this->pauseButton.render(target);

	if (!this->ArraySwitch)
	{
		for (int i = 0; i < this->planetArray.size(); i++)
		{
			this->planetArray[i].render(target);
		}
	}
	else if (this->ArraySwitch)
	{
		for (int i = 0; i < this->sataliteArray.size(); i++)
		{
			this->sataliteArray[i].render(target);
		}
	}
}