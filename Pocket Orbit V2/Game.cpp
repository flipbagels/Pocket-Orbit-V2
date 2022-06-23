#include <iostream>
#include "Game.h"


//Private Functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.width = 1500;
	this->videoMode.height = 1000;
	//this->videoMode.width = sf::VideoMode::getDesktopMode().width;
	//this->videoMode.height = sf::VideoMode::getDesktopMode().height;

	this->window = new sf::RenderWindow(this->videoMode, "Pocket Orbit",
		sf::Style::Titlebar | sf::Style::Close /*| sf::Style::Fullscreen*/);

	this->window->setFramerateLimit(60);
}

void Game::initRadii()
{
	this->radiusMap.insert(std::make_pair("Sun", 80.0f));
	this->radiusMap.insert(std::make_pair("Comet", 8.0f));
	this->radiusMap.insert(std::make_pair("Mercury", 9.0f));
	this->radiusMap.insert(std::make_pair("Venus", 13.0f));
	this->radiusMap.insert(std::make_pair("Earth", 13.0f));
	this->radiusMap.insert(std::make_pair("Mars", 11.0f));
	this->radiusMap.insert(std::make_pair("Jupiter", 26.0f));
	this->radiusMap.insert(std::make_pair("Saturn", 24.0f));
	this->radiusMap.insert(std::make_pair("Uranus", 19.0f));
	this->radiusMap.insert(std::make_pair("Neptune", 17.0f));
	this->radiusMap.insert(std::make_pair("Pluto", 8.0f));

	this->radiusMap.insert(std::make_pair("Moon", 10.0f));
	this->radiusMap.insert(std::make_pair("ISS", 12.0f));
	this->radiusMap.insert(std::make_pair("Satalite_red", 15.0f));

	this->radiusMap.insert(std::make_pair("Missile", 4.0f));
	this->radiusMap.insert(std::make_pair("Nuclear", 4.0f));
}

void Game::initIndexMaps()
{
	this->starIndexMap.insert(std::make_pair(0, "Sun"));

	this->cometIndexMap.insert(std::make_pair(0, "Comet"));

	this->planetIndexMap.insert(std::make_pair(0, "Mercury"));
	this->planetIndexMap.insert(std::make_pair(1, "Venus"));
	this->planetIndexMap.insert(std::make_pair(2, "Earth"));
	this->planetIndexMap.insert(std::make_pair(3, "Mars"));
	this->planetIndexMap.insert(std::make_pair(4, "Jupiter"));
	this->planetIndexMap.insert(std::make_pair(5, "Saturn"));
	this->planetIndexMap.insert(std::make_pair(6, "Uranus"));
	this->planetIndexMap.insert(std::make_pair(7, "Neptune"));
	this->planetIndexMap.insert(std::make_pair(8, "Pluto"));

	this->sataliteIndexMap.insert(std::make_pair(0, "Moon"));
	this->sataliteIndexMap.insert(std::make_pair(1, "Satalite_red"));
	this->sataliteIndexMap.insert(std::make_pair(2, "ISS"));

	this->weaponIndexMap.insert(std::make_pair(0, "Missile"));
	this->weaponIndexMap.insert(std::make_pair(1, "Nuclear"));

}

void Game::initTextures()
{
	// Title Text
	this->assignTexture("Textures/TitleText2.png", "TitleText");

	// Level Select Frame
	this->assignTexture("Textures/LevelSelectFrame.png", "LevelSelectFrame");
	this->assignTexture("Textures/LevelSelectFrameSelected.png", "LevelSelectFrameSelected");
	this->assignTexture("Textures/Sandbox.png", "Sandbox");

	// Buttons
	this->assignTexture("Textures/StartButton.png", "StartButton");
	this->assignTexture("Textures/PauseButton.png", "PauseButton");
	this->assignTexture("Textures/RestartButton.png", "RestartButton");
	this->assignTexture("Textures/HomeButton.png", "HomeButton");
	this->assignTexture("Textures/LevelSelectButton.png", "LevelSelectButton");

	// Sun
	this->assignTexture("Textures/Sun.png", "Sun");

	// Planets
	this->assignTexture("Textures/Comet.png", "Comet");
	this->assignTexture("Textures/Mercury.png", "Mercury");
	this->assignTexture("Textures/Venus.png", "Venus");
	this->assignTexture("Textures/Earth.png", "Earth");
	this->assignTexture("Textures/Mars.png", "Mars");
	this->assignTexture("Textures/Jupiter.png", "Jupiter");
	this->assignTexture("Textures/Saturn.png", "Saturn");
	this->assignTexture("Textures/Uranus.png", "Uranus");
	this->assignTexture("Textures/Neptune.png", "Neptune");
	this->assignTexture("Textures/Pluto.png", "Pluto");

	// Moons
	this->assignTexture("Textures/Moon.png", "Moon");
	this->assignTexture("Textures/ISS.png", "ISS");
	this->assignTexture("Textures/Satalite_red.png", "Satalite_red");

	// Weapons
	this->assignTexture("Textures/Missile.png", "Missile");
	this->assignTexture("Textures/Nuclear.png", "Nuclear");
}

void Game::initFonts()
{
	if (!font.loadFromFile("Fonts/Ubuntu-Title.ttf"))
	{
		std::cout << "Failed to load gameFont" << std::endl;
	}

	this->score = Score(this->font, this->videoMode);
}

void Game::initObjects()
{
	this->titleScreen = TitleScreen(float(this->videoMode.width / 2), float((this->videoMode.height / 2) - 100.0f), this->textureMap["TitleText"], this->textureMap["Earth"], this->textureMap["StartButton"]);
	this->levelSelect = LevelSelect(float(this->videoMode.width), float(this->videoMode.height), this->textureMap);
	this->level_1UI = Level_1UI(float(this->videoMode.width), float(this->videoMode.height), this->textureMap);
	this->level_2UI = Level_2UI(float(this->videoMode.width), float(this->videoMode.height), this->textureMap);
	this->level_3UI = Level_3UI(float(this->videoMode.width), float(this->videoMode.height), this->textureMap);
	this->sandboxUI = SandboxUI(float(this->videoMode.width), float(this->videoMode.height), this->planetIndexMap, this->sataliteIndexMap, this->textureMap);
	this->pauseUI = PauseUI(this->videoMode, this->textureMap);
	this->postGameUI = PostGameUI(this->font, this->videoMode, this->textureMap);
}

// Constructor / Destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initRadii();
	this->initIndexMaps();
	this->initTextures();
	this->initFonts();
	this->initObjects();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}


// Functions
void Game::resetSpaceObjArray(std::string centreObj, std::string centreObjType)
{
	this->spaceObjArray.clear();
	this->spaceObjArray.push_back(SpaceObj(sf::Vector2f(this->videoMode.width / 2, this->videoMode.height / 2), sf::Vector2f(0.0f, 0.0f), this->radiusMap[centreObj], centreObjType, 0, this->textureMap[centreObj]));
}

void Game::updateAllowInput()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->allowInput = true;
	}
}

void Game::updateAllowInputUI()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->allowInputUI = true;
	}
}

void Game::assignTexture(std::string fileName, std::string mapName)
{
	sf::Texture texture;
	texture.loadFromFile(fileName);
	texture.setSmooth(true);
	this->textureMap.insert(std::make_pair(mapName, texture));
}

std::string Game::randomSpaceObj(std::map<int, std::string> indexMap_in) const
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> Dist(0, indexMap_in.size());
	std::string currentPlanet_out;

	return indexMap_in[int(Dist(rng))];
}

void Game::pollEvents()
{
	// Event polling
	while (this->window->pollEvent(ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->gameState == "TitleScreen" && this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		case sf::Event::MouseWheelMoved:
			if (this->gameState == "Level_1" && !this->pauseUI.isPaused() && !this->postGameUI.isPostGameActive())
			{
				this->panZoom.changeZoomMouseLimited(ev, *this->window, this->videoMode, this->panZoom.offsetMax1_x, this->panZoom.offsetMax1_y);
			}
			else if (this->gameState == "Level_2" && !this->pauseUI.isPaused() && !this->postGameUI.isPostGameActive())
			{
				this->panZoom.changeZoomMouseLimited(ev, *this->window, this->videoMode, this->panZoom.offsetMax2_x, this->panZoom.offsetMax2_y);
			}
			else if (this->gameState == "Level_3" && !this->pauseUI.isPaused() && !this->postGameUI.isPostGameActive())
			{
				this->panZoom.changeZoomMouseLimited(ev, *this->window, this->videoMode, this->panZoom.offsetMax3_x, this->panZoom.offsetMax3_y);
			}
			else if (this->gameState == "Sandbox" && !this->pauseUI.isPaused())
			{
				if (this->orbitTargetID == 0)
				{
					this->panZoom.changeZoomMouseUnlimited(ev, *this->window);
				}
				else
				{
					this->panZoom.changeZoomTarget(ev, *this->window, this->spaceObjArray[this->orbitTargetID].getPosition());
				}
			}
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();

	// Updates the selected game state
	if (this->gameState == "TitleScreen")
	{
		this->updateTitleScreen();
	}
	else if (this->gameState == "LevelSelect")
	{
		this->updateLevelSelect();
	}
	else if (this->gameState == "Level_1")
	{
		if (!this->pauseUI.isPaused() && !this->postGameUI.isPostGameActive())
		{
			this->updateLevel_1();
		}
		else if (this->pauseUI.isPaused())
		{
			this->updatePause();
		}
		else if (this->postGameUI.isPostGameActive())
		{
			this->updatePostGame();
		}
	}
	else if (this->gameState == "Level_2")
	{
		if (!this->pauseUI.isPaused() && !this->postGameUI.isPostGameActive())
		{
			this->updateLevel_2();
		}
		else if (this->pauseUI.isPaused())
		{
			this->updatePause();
		}
		else if (this->postGameUI.isPostGameActive())
		{
			this->updatePostGame();
		}
	}
	else if (gameState == "Level_3")
	{
		if (!this->pauseUI.isPaused() && !this->postGameUI.isPostGameActive())
		{
			this->updateLevel_3();
		}
		else if (this->pauseUI.isPaused())
		{
			this->updatePause();
		}
		else if (this->postGameUI.isPostGameActive())
		{
			this->updatePostGame();
		}
	}
	else if (this->gameState == "Sandbox")
	{
		if (!this->pauseUI.isPaused() && !this->postGameUI.isPostGameActive())
		{
			this->updateSandbox();
		}
		else if (this->pauseUI.isPaused())
		{
			this->updatePause();
		}
	}
}

void Game::render()
{
	// Clears frame
	this->window->clear();

	// Checks and renders selected game state
	if (this->gameState == "TitleScreen")
	{
		this->renderTitleScreen();
	}
	else if (this->gameState == "LevelSelect")
	{
		this->renderLevelSelect();
	}
	else if (this->gameState == "SandBox")
	{
		this->renderSandbox();
	}
	else if (this->gameState == "Level_1")
	{
		this->renderLevel_1();
		if (this->pauseUI.isPaused())
		{
			this->renderPause();
		}
		if (this->postGameUI.isPostGameActive())
		{
			this->renderPostGame();
		}
	}
	else if (this->gameState == "Level_2")
	{
		this->renderLevel_2();
		if (this->pauseUI.isPaused())
		{
			this->renderPause();
		}
		if (this->postGameUI.isPostGameActive())
		{
			this->renderPostGame();
		}
	}
	else if (this->gameState == "Level_3")
	{
		this->renderLevel_3();
		if (this->pauseUI.isPaused())
		{
			this->renderPause();
		}
		if (this->postGameUI.isPostGameActive())
		{
			this->renderPostGame();
		}
	}
	else if (this->gameState == "Sandbox")
	{
		this->renderSandbox();
		if (this->pauseUI.isPaused())
		{
			this->renderPause();
		}
	}

	// Displays frame
	this->window->display();
	std::cout << this->sandboxUI.getLaunchIndex() << std::endl;
}

// Pause
void Game::updatePause()
{
	if (!this->pauseUI.isMouseOnUI(*this->window))
	{
		this->allowInputUI = false;
	}
	if (this->allowInputUI == false)
	{
		this->updateAllowInputUI();
	}

	if (this->allowInputUI == true)
	{
		this->pauseUI.updateButtons(*this->window);
		if (this->pauseUI.isLevelSelectPressed(*this->window))
		{
			if (this->gameState == "Level_1")
			{
				this->resetLevel_1();
			}
			else if (this->gameState == "Level_2")
			{
				this->resetLevel_2();
			}
			else if (this->gameState == "Level_3")
			{
				this->resetLevel_3();
			}
			else if (this->gameState == "Sandbox")
			{
				this->resetSandbox();
			}
			this->gameState = "LevelSelect";
			this->allowInputUI = false;
			this->pauseUI.unPause();
		}
		else if (this->pauseUI.isRestartPressed(*this->window))
		{
			if (this->gameState == "Level_1")
			{
				this->resetLevel_1();
			}
			else if (this->gameState == "Level_2")
			{
				this->resetLevel_2();
			}
			else if (this->gameState == "Level_3")
			{
				this->resetLevel_3();
			}
			else if (this->gameState == "Sandbox")
			{
				this->resetSandbox();
			}
			this->pauseUI.unPause();
			this->allowInputUI = false;
		}
		else if (this->pauseUI.isStartPressed(*this->window))
		{
			this->pauseUI.unPause();
			this->allowInputUI = false;
		}
	}
}

void Game::renderPause()
{
	this->pauseUI.render(*this->window);
}

// Post Game
void Game::updatePostGame()
{
	if (!this->postGameUI.isMouseOnUI(*this->window))
	{
		this->allowInputUI = false;
	}
	if (this->allowInputUI == false)
	{
		this->updateAllowInputUI();
	}

	if (this->allowInputUI == true)
	{
		this->postGameUI.updateButtons(*this->window);
		if (this->postGameUI.isLevelSelectPressed(*this->window))
		{
			if (this->gameState == "Level_1")
			{
				this->resetLevel_1();
			}
			else if (this->gameState == "Level_2")
			{
				this->resetLevel_2();
			}
			else if (this->gameState == "Level_3")
			{
				this->resetLevel_3();
			}
			else if (this->gameState == "Sandbox")
			{
				this->resetSandbox();
			}
			this->gameState = "LevelSelect";
			this->allowInputUI = false;
			this->postGameUI.endPostGame();
		}
		else if (this->postGameUI.isRestartPressed(*this->window))
		{
			if (this->gameState == "Level_1")
			{
				this->resetLevel_1();
			}
			else if (this->gameState == "Level_2")
			{
				this->resetLevel_2();
			}
			else if (this->gameState == "Level_3")
			{
				this->resetLevel_3();
			}
			else if (this->gameState == "Sandbox")
			{
				this->resetSandbox();
			}
			this->postGameUI.endPostGame();
		}
	}
}

void Game::renderPostGame()
{
	this->postGameUI.render(*this->window, this->score);
}

// Title Screen Functions
void Game::updateTitleScreen()
{
	if (!this->titleScreen.isMouseOnUI(*this->window))
	{
		this->allowInputUI = false;
	}
	if (this->allowInputUI == false)
	{
		this->updateAllowInputUI();
	}

	this->titleScreen.updateEarth();
	this->titleScreen.updateEarthTrail();
	if (this->allowInputUI == true)
	{
		this->titleScreen.updateButtons(*this->window);
		if (this->titleScreen.isStartPressed(*this->window))
		{
			this->gameState = "LevelSelect";
			this->titleScreen.reset();
			this->allowInputUI = false;
		}
	}
}
void Game::renderTitleScreen()
{
	this->titleScreen.render(*this->window);
}

// Level Select Functions
void Game::updateLevelSelect()
{
	if (!this->levelSelect.isMouseOnUI(*this->window))
	{
		this->allowInputUI = false;
	}
	if (this->allowInputUI == false)
	{
		this->updateAllowInputUI();
	}

	if (this->allowInputUI == true)
	{
		this->levelSelect.updateLevelSelectFrame(*this->window, this->textureMap);
		this->levelSelect.updateButtons(*this->window);
		if (this->levelSelect.isHomePressed(*this->window))
		{
			this->gameState = "TitleScreen";
			this->allowInputUI = false;
			this->levelSelect.reset(this->textureMap);
		}
		if (this->levelSelect.isLevelPressed(*this->window))
		{
			this->gameState = levelSelect.whichLevel(*this->window);
			this->allowInput = false;
			this->allowInputUI = false;
			this->levelSelect.reset(this->textureMap);
			if (this->gameState == "Level_1")
			{
				this->resetLevel_1();
			}
			else if (this->gameState == "Level_2")
			{
				this->resetLevel_2();
			}
			else if (this->gameState == "Level_3")
			{
				this->resetLevel_3();
			}
			else if (this->gameState == "Sandbox")
			{
				this->resetSandbox();
			}
		}
	}
}
void Game::renderLevelSelect()
{
	this->levelSelect.render(*this->window);
}

// Level_1 Functions
void Game::updateLevel_1()
{
	// Updates allowInput
	if (this->level_1UI.isMouseOnUI(*this->window))
	{
		this->allowInput = false;
	}
	if (this->allowInput == false)
	{
		this->updateAllowInput();
	}

	if (!this->level_1UI.isMouseOnUI(*this->window))
	{
		this->allowInputUI = false;
	}
	if (this->allowInputUI == false)
	{
		this->updateAllowInputUI();
	}

	// updates UI buttons
	if (this->allowInputUI == true)
	{
		this->level_1UI.updateButtons(*this->window);
		if (this->level_1UI.isPausePressed(*this->window))
		{
			this->pauseUI.doPause();
			this->allowInput = false;
			this->allowInputUI = false;
		}
	}

	// Updates pan. (zoom updated in polling())
	this->panZoom.changePanLimited(*this->window, this->videoMode, this->panZoom.offsetMax1_x, this->panZoom.offsetMax1_y);

	for (int i = 1; i < this->spaceObjArray.size(); i++)
	{
		// Updates position of space objects
		this->spaceObjArray[i].updatePos(this->spaceObjArray);

		// Checks and updates collisions between space objects
		for (int j = 1; j < this->spaceObjArray.size(); j++)
		{
			if (this->spaceObjArray[i].isCollidedWith(this->spaceObjArray[j]) && i != j)
			{
				this->spaceObjArray[i].updateCollision(this->spaceObjArray[j]);
			}
		}

		// Updates trail on comets
		this->spaceObjArray[i].updateRedTrail(this->spaceObjArray[0]);

		// Checks and updates collisitons between space objects and sun
		if (this->spaceObjArray[i].isCollidedWithSun(this->spaceObjArray[0]))
		{
			this->spaceObjArray.erase(this->spaceObjArray.begin() + i);
		}
	}
	for (int i = 1; i < this->spaceObjArray.size(); i++)
	{
		// Checks and updates collisions between space obejct and target circle
		if (this->spaceObjArray[i].isCollidedWith(this->targetCircle))
		{
			this->spawnCircle.respawnToTarget(this->targetCircle);
			this->targetCircle.decreaseSize();
			this->targetCircle.respawn(this->videoMode, this->panZoom.offsetMax1_x, this->panZoom.offsetMax1_y, this->level_1MinSpawnDistFromSun, this->spawnCircle.getPosition());
			this->resetSpaceObjArray("Sun", "Star");
			this->launchCounter.reset();
			this->score.increaseScoreCounter();
			this->allowInput = false;
		}
	}

	// Creates launch line and new space object
	if ((this->allowInput == true || this->launchLine.updateLineInhibit == true) && this->launchCounter.getCount() < this->level_1LaunchCounterMax)
	{
		// Updates Spawn Circle
		this->spawnCircle.updateSpawnCircle(*this->window, this->panZoom);

		this->frameCounter.reset();
		this->launchLine.updateLine(*this->window, this->spawnCircle, this->panZoom);
		if (this->launchLine.isReadyForLaunch())
		{
			this->spaceObjArray.push_back(SpaceObj(this->launchLine.screenToWorld(this->panZoom), this->radiusMap["Comet"], "Comet", 0, this->textureMap["Comet"]));
			this->launchCounter.increase(); // Used to limit the number of objects launched
		}
	}
	else if (this->allowInput == true)
	{
		this->launchLine.reset();
		this->frameCounter.increase();
		if (this->frameCounter.getCount() >= 450)
		{
			this->postGameUI.beginPostGame();
			this->allowInput = false;
			this->allowInputUI = false;
		}
	}
}
void Game::renderLevel_1()
{
	for (int i = 0; i < spaceObjArray.size(); i++)
	{
		this->spaceObjArray[i].worldToScreen(this->panZoom).render(*this->window);
	}
	if (this->launchCounter.getCount() < this->level_1LaunchCounterMax)
	{
		this->spawnCircle.worldToScreen(this->panZoom).render(*this->window);
	}
	this->targetCircle.worldToScreen(this->panZoom).render(*this->window);
	this->launchLine.render(*this->window);
	this->level_1UI.render(*this->window);
	this->score.render(*this->window);
}

void Game::resetLevel_1()
{
	this->resetSpaceObjArray("Sun", "Star");
	this->launchLine.reset();
	this->panZoom.reset();
	this->panZoom.setZoom(this->videoMode.width / (this->videoMode.width + (2 * this->panZoom.offsetMax1_x)));
	this->launchCounter.reset();
	this->frameCounter.reset();
	this->spawnCircle.respawn(this->videoMode, this->panZoom.offsetMax1_x, this->panZoom.offsetMax1_y, this->level_1MinSpawnDistFromSun);
	this->spawnCircle.resetSize();
	this->targetCircle.respawn(this->videoMode, this->panZoom.offsetMax1_x, this->panZoom.offsetMax1_y, this->level_1MinSpawnDistFromSun, this->spawnCircle.getPosition());
	this->targetCircle.resetSize();
	this->score.resetScoreCounter();
}

// Level_2 Functions
void Game::updateLevel_2()
{
	// Updates allowInput
	if (this->level_2UI.isMouseOnUI(*this->window))
	{
		this->allowInput = false;
	}
	if (this->allowInput == false)
	{
		this->updateAllowInput();
	}

	if (!this->level_2UI.isMouseOnUI(*this->window))
	{
		this->allowInputUI = false;
	}
	if (this->allowInputUI == false)
	{
		this->updateAllowInputUI();
	}

	// updates UI buttons
	if (this->allowInputUI == true)
	{
		this->level_2UI.updateButtons(*this->window);
		if (this->level_2UI.isPausePressed(*this->window))
		{
			this->pauseUI.doPause();
			this->allowInput = false;
			this->allowInputUI = false;
		}
	}

	// Updates pan. (zoom updated in polling())
	this->panZoom.changePanLimited(*this->window, this->videoMode, this->panZoom.offsetMax2_x, this->panZoom.offsetMax2_y);

	for (int i = 1; i < this->spaceObjArray.size(); i++)
	{
		// Updates position of space objects
		this->spaceObjArray[i].updatePos(this->spaceObjArray);

		// Checks and updates collisions between space objects
		for (int j = 1; j < this->spaceObjArray.size(); j++)
		{
			if (this->spaceObjArray[i].isCollidedWith(this->spaceObjArray[j]) && i != j)
			{
				this->spaceObjArray[i].updateCollision(this->spaceObjArray[j]);
			}
		}

		// Updates trail on comets
		this->spaceObjArray[i].updateRedTrail(this->spaceObjArray[0]);

		// Checks and updates collisitons between space objects and sun
		if (this->spaceObjArray[i].isCollidedWithSun(this->spaceObjArray[0]))
		{
			this->spaceObjArray.erase(this->spaceObjArray.begin() + i);
		}
	}
	for (int i = 1; i < this->spaceObjArray.size(); i++)
	{
		// Checks and updates collisions between space obejct and target circle
		if (this->spaceObjArray[i].isCollidedWith(this->targetCircle))
		{
			this->spawnCircle.respawnToTarget(this->targetCircle);
			this->targetCircle.decreaseSize();
			this->targetCircle.respawn(this->videoMode, this->panZoom.offsetMax2_x, this->panZoom.offsetMax2_y, this->level_2MinSpawnDistFromSun, this->spawnCircle.getPosition());
			this->resetSpaceObjArray("Sun", "Star");
			this->launchCounter.reset();
			this->score.increaseScoreCounter();
			this->allowInput = false;
		}
	}

	// Creates launch line and new space object
	if ((this->allowInput == true || this->launchLine.updateLineInhibit == true) && this->launchCounter.getCount() < this->level_2LaunchCounterMax)
	{
		// Updates Spawn Circle
		this->spawnCircle.updateSpawnCircle(*this->window, this->panZoom);

		this->frameCounter.reset();
		this->launchLine.updateLine(*this->window, this->spawnCircle, this->panZoom);
		if (this->launchLine.isReadyForLaunch())
		{
			this->spaceObjArray.push_back(SpaceObj(this->launchLine.screenToWorld(this->panZoom), this->radiusMap[this->currentPlanet], "Planet", 0, this->textureMap[this->currentPlanet]));
			this->launchCounter.increase(); // Used to limit the number of objects launched

			std::string newCurrentPlanet;
			do
			{
				newCurrentPlanet = this->randomSpaceObj(this->planetIndexMap);
			} while (newCurrentPlanet == this->currentPlanet);
			this->currentPlanet = newCurrentPlanet;
			this->level_2UI.setCurrentPlanetTexture(this->textureMap[this->currentPlanet]);
		}
	}
	else if (this->allowInput == true)
	{
		this->launchLine.reset();
		this->frameCounter.increase();
		if (this->frameCounter.getCount() >= 450)
		{
			this->postGameUI.beginPostGame();
			this->allowInput = false;
			this->allowInputUI = false;
		}
	}

}
void Game::renderLevel_2()
{
	for (int i = 0; i < spaceObjArray.size(); i++)
	{
		this->spaceObjArray[i].worldToScreen(this->panZoom).render(*this->window);
	}
	if (this->launchCounter.getCount() < this->level_2LaunchCounterMax)
	{
		this->spawnCircle.worldToScreen(this->panZoom).render(*this->window);
	}
	this->targetCircle.worldToScreen(this->panZoom).render(*this->window);
	this->launchLine.render(*this->window);
	this->level_2UI.render(*this->window);
	this->score.render(*this->window);
}

void Game::resetLevel_2()
{
	this->resetSpaceObjArray("Sun", "Star");
	this->launchLine.reset();
	this->panZoom.reset();
	this->panZoom.setZoom(this->videoMode.width / (this->videoMode.width + (2 * this->panZoom.offsetMax2_x)));
	this->launchCounter.reset();
	this->frameCounter.reset();
	this->spawnCircle.respawn(this->videoMode, this->panZoom.offsetMax2_x, this->panZoom.offsetMax2_y, this->level_2MinSpawnDistFromSun);
	this->spawnCircle.resetSize();
	this->targetCircle.respawn(this->videoMode, this->panZoom.offsetMax2_x, this->panZoom.offsetMax2_y, this->level_2MinSpawnDistFromSun, this->spawnCircle.getPosition());
	this->targetCircle.resetSize();
	this->score.resetScoreCounter();
	this->currentPlanet = this->randomSpaceObj(this->planetIndexMap);
	this->level_2UI.setCurrentPlanetTexture(this->textureMap[this->currentPlanet]);
}

// Level_3 Functions
void Game::updateLevel_3()
{
	// Updates allowInput
	if (this->level_3UI.isMouseOnUI(*this->window))
	{
		this->allowInput = false;
	}
	if (this->allowInput == false)
	{
		this->updateAllowInput();
	}

	if (!this->level_3UI.isMouseOnUI(*this->window))
	{
		this->allowInputUI = false;
	}
	if (this->allowInputUI == false)
	{
		this->updateAllowInputUI();
	}

	// updates UI buttons
	if (this->allowInputUI == true)
	{
		this->level_3UI.updateButtons(*this->window);
		if (this->level_3UI.isPausePressed(*this->window))
		{
			this->pauseUI.doPause();
			this->allowInput = false;
			this->allowInputUI = false;
		}
	}

	// Updates pan. (zoom updated in polling())
	this->panZoom.changePanLimited(*this->window, this->videoMode, this->panZoom.offsetMax3_x, this->panZoom.offsetMax3_y);

	// Updates frame counter
	this->frameCounter.increase();

	// Spawn objects spawning
	if (this->score.getScoreCounter() < 5)
	{
		if (this->frameCounter.getCount() >= 240 || this->spawnObjArray.size() == 0)
		{
			this->spawnObjArray.push_back(SpawnObj(this->videoMode, this->panZoom.offsetMax3_x, this->panZoom.offsetMax3_y, this->textureMap["Comet"]));
			this->frameCounter.reset();
		}
	}
	else if (this->score.getScoreCounter() < 10)
	{
		if (this->frameCounter.getCount() >= 180 || this->spawnObjArray.size() == 0)
		{
			this->spawnObjArray.push_back(SpawnObj(this->videoMode, this->panZoom.offsetMax3_x, this->panZoom.offsetMax3_y, this->textureMap["Comet"]));
			this->frameCounter.reset();
		}
	}
	else
	{
		if (this->frameCounter.getCount() >= 150 || this->spawnObjArray.size() == 0)
		{
			this->spawnObjArray.push_back(SpawnObj(this->videoMode, this->panZoom.offsetMax3_x, this->panZoom.offsetMax3_y, this->textureMap["Comet"]));
			this->frameCounter.reset();
		}
	}

	for (int i = 1; i < this->spaceObjArray.size(); i++)
	{
		// Updates position of space objects
		this->spaceObjArray[i].updatePos(this->spaceObjArray);

		// Checks and updates collisions between space objects
		for (int j = 1; j < this->spaceObjArray.size(); j++)
		{
			if (this->spaceObjArray[i].isCollidedWith(this->spaceObjArray[j]) && i != j)
			{
				this->spaceObjArray[i].updateCollision(this->spaceObjArray[j]);
			}
		}

		// Updates trail on comets
		this->spaceObjArray[i].updateRedTrail(this->spaceObjArray[0]);

		// Checks and updates collisitons between space objects and sun
		if (this->spaceObjArray[i].isCollidedWith(this->spaceObjArray[0]))
		{
			this->spaceObjArray[0].setOutlineColor(sf::Color::Red);
			this->postGameUI.beginPostGame();
			this->allowInput = false;
			this->allowInputUI = false;
		}
	}
	for (int i = 0; i < this->spawnObjArray.size(); i++)
	{
		// Updates position of spawnObj
		this->spawnObjArray[i].updatePos();

		// Updates outline of spawnObj
		this->spawnObjArray[i].updateOutline(this->videoMode);

		// Checks and updates collisions between spawnObj and earth
		if (this->spaceObjArray[0].isCollidedWith(this->spawnObjArray[i]))
		{
			this->postGameUI.beginPostGame();
			this->spaceObjArray[0].setOutlineColor(sf::Color::Red);
			this->allowInput = false;
			this->allowInputUI = false;
		}
	}
	for (int i = 1; i < this->spaceObjArray.size(); i++)
	{
		for (int j = 0; j < this->spawnObjArray.size(); j++)
		{
			// Checks and updates collisions between space obejct and spawn object
			if (this->spaceObjArray[i].isCollidedWith(this->spawnObjArray[j]))
			{
				this->spawnObjArray.erase(this->spawnObjArray.begin() + j);
				this->launchCounter.reset();
				this->resetSpaceObjArray("Earth", "Planet");
				this->score.increaseScoreCounter();
				this->allowInput = false;
			}
		}
	}

	// Creates launch line and new space object
	if ((this->allowInput == true || this->launchLine.updateLineInhibit == true) && this->launchCounter.getCount() < this->level_3LaunchCounterMax)
	{
		// Updates spawn rectangle
		this->spawnRectangle.updateSpawnRectangle(*this->window, this->panZoom);

		this->launchLine.updateLine(*this->window, this->spawnRectangle, this->panZoom);
		if (this->launchLine.isReadyForLaunch())
		{
			this->spaceObjArray.push_back(SpaceObj(this->launchLine.screenToWorld(this->panZoom), this->radiusMap["Missile"], "Weapon", 0, this->textureMap["Missile"]));
			this->launchCounter.increase(); // Used to limit the number of objects launched
		}
	}
	else if (this->allowInput == true)
	{
		this->launchLine.reset();
	}
}
void Game::renderLevel_3()
{
	for (int i = 0; i < spaceObjArray.size(); i++)
	{
		this->spaceObjArray[i].worldToScreen(this->panZoom).render(*this->window);
	}
	for (int i = 0; i < spawnObjArray.size(); i++)
	{
		this->spawnObjArray[i].worldToScreen(this->panZoom).render(*this->window);
	}
	if (this->launchCounter.getCount() < this->level_3LaunchCounterMax)
	{
		this->spawnRectangle.worldToScreen(this->panZoom).render(*this->window);
	}
	this->launchLine.render(*this->window);
	this->level_3UI.render(*this->window);
	this->score.render(*this->window);
}

void Game::resetLevel_3()
{
	this->resetSpaceObjArray("Earth", "Planet");
	this->launchLine.reset();
	this->panZoom.reset();
	this->panZoom.setZoom(this->videoMode.width / (this->videoMode.width + (2 * this->panZoom.offsetMax3_x)));
	this->launchCounter.reset();
	this->frameCounter.reset();
	this->spawnRectangle.reset(this->videoMode, this->panZoom.offsetMax3_y);
	this->score.resetScoreCounter();
	this->spawnObjArray.clear();
	this->spawnObjArray.push_back(SpawnObj(this->videoMode, this->panZoom.offsetMax3_x, this->panZoom.offsetMax3_y, this->textureMap["Comet"]));
}

// Sandbox Functions
void Game::updateSandbox()
{
	// Updates allowInput
	if (this->sandboxUI.isMouseOnUI(*this->window))
	{
		this->allowInput = false;
	}
	if (this->allowInput == false)
	{
		this->updateAllowInput();
	}

	if (!this->sandboxUI.isMouseOnUI(*this->window))
	{
		this->allowInputUI = false;
	}
	if (this->allowInputUI == false)
	{
		this->updateAllowInputUI();
	}

	// Updates UI buttons
	if (this->allowInputUI == true)
	{
		this->sandboxUI.updateButtons(*this->window);
		this->sandboxUI.updateLaunchIndex(*this->window);
		if (this->sandboxUI.isPausePressed(*this->window))
		{
			this->pauseUI.doPause();
			this->allowInput = false;
			this->allowInputUI = false;
		}
	}

	// Updates SpaceObj Selection
	for (int i = 1; i < this->spaceObjArray.size(); i++)
	{
		if (this->spaceObjArray[i].getType() == "Planet")
		{
			this->spaceObjArray[i].updateOutlineColor(*this->window, this->panZoom);
		}

		if (this->spaceObjArray[i].isPressed(*this->window, this->panZoom))
		{
			if (i == this->orbitTargetID)
			{
				this->orbitTargetID = 0;
				this->sandboxUI.planetLaunch();
			}
			else if (this->spaceObjArray[i].getType() == "Planet")
			{
				this->orbitTargetID = i;
				this->sandboxUI.sataliteLaunch();
			}

			this->allowInput = false;
		}
	}

	// Updates pan. (zoom updated in polling())
	this->panZoom.changePanUnlimited(*this->window);
	this->panZoom.adjustPanTarget(*this->window, this->videoMode, this->orbitTargetID, this->spaceObjArray[this->orbitTargetID].getPosition());

	// Updates general SpaceObj properties
	for (int i = 1; i < this->spaceObjArray.size(); i++)
	{
		// Updates position of space objects
		this->spaceObjArray[i].updatePos(this->spaceObjArray);

		// Checks and updates collisions between space objects
		for (int j = 1; j < this->spaceObjArray.size(); j++)
		{
			if (this->spaceObjArray[i].isCollidedWith(this->spaceObjArray[j]) && i != j)
			{
				this->spaceObjArray[i].updateCollision(this->spaceObjArray[j]);
			}
		}

		// Updates trail on comets
		this->spaceObjArray[i].updateRedTrail(this->spaceObjArray[0]);
	}

	// Checks and updates collisitons between space objects and sun
	for (int i = 1; i < this->spaceObjArray.size(); i++)
	{
		if (this->spaceObjArray[i].isCollidedWithSun(this->spaceObjArray[0]))
		{
			for (int j = i; j < this->spaceObjArray.size(); j++)
			{
				if (this->spaceObjArray[j].getTargetID() == i)
				{
					this->spaceObjArray[j].setTargetID(0);
				}
				else if (this->spaceObjArray[j].getTargetID() > i)
				{
					this->spaceObjArray[j].setTargetID(this->spaceObjArray[j].getTargetID() - 1);
				}
			}
			if (i == this->orbitTargetID)
			{
				this->orbitTargetID = 0;
				this->sandboxUI.planetLaunch();
			}
			else if (this->orbitTargetID > i)
			{
				this->orbitTargetID--;
			}

			this->spaceObjArray.erase(this->spaceObjArray.begin() + i);
		}
	}



	// Creates launch line and new space object
	if (this->allowInput == true || this->launchLine.updateLineInhibit == true)
	{
		this->launchLine.updateLine(*this->window, this->panZoom);
		if (this->launchLine.isReadyForLaunch())
		{
			if (!this->sandboxUI.getArraySwitch())
			{
				this->spaceObjArray.push_back(SpaceObj(this->launchLine.screenToWorld(this->panZoom), this->radiusMap[this->planetIndexMap[this->sandboxUI.getLaunchIndex()]], "Planet", this->orbitTargetID, this->textureMap[this->planetIndexMap[this->sandboxUI.getLaunchIndex()]]));
			}
			else if (this->sandboxUI.getArraySwitch())
			{
				this->spaceObjArray.push_back(SpaceObj(this->launchLine.screenToWorld(this->panZoom), this->radiusMap[this->sataliteIndexMap[this->sandboxUI.getLaunchIndex()]], "Satalite", this->orbitTargetID, this->textureMap[this->sataliteIndexMap[this->sandboxUI.getLaunchIndex()]]));
			}
		}
	}

}
void Game::renderSandbox()
{
	for (int i = 0; i < spaceObjArray.size(); i++)
	{
		this->spaceObjArray[i].worldToScreen(this->panZoom).render(*this->window);
	}
	this->launchLine.render(*this->window);
	this->sandboxUI.render(*this->window);
}

void Game::resetSandbox()
{
	this->resetSpaceObjArray("Sun", "Star");
	this->launchLine.reset();
	this->panZoom.reset();
	this->panZoom.setZoom(1.0f);
	this->orbitTargetID = 0;
	this->sandboxUI.planetLaunch();
}