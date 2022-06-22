#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "FrameTimer.h"
#include "Counter.h"
#include "TitleScreen.h"
#include "LevelSelect.h"
#include "Level_1UI.h"
#include "Level_2UI.h"
#include "Level_3UI.h"
#include "SandboxUI.h"
#include "SpaceObj.h"
#include "Line.h"
#include "PauseUI.h"
#include "PostGameUI.h"
#include "PanZoom.h"
#include "SpawnCircle.h"
#include "TargetCircle.h"
#include "SpawnRectangle.h"
#include "Score.h"

#include <random>

class Game
{
private:
	// Private Functions
	void initVariables();
	void initWindow();
	void initRadii();
	void initIndexMaps();
	void initTextures();
	void initFonts();
	void initObjects();

	// Private Variables
	sf::VideoMode videoMode;
	sf::Event ev;
	std::string gameState = "TitleScreen";
	sf::Font font;
	bool allowInput = true;
	bool allowInputUI = true;
	int orbitTargetID = 0;
	std::string currentStar = "Sun";
	std::string currentPlanet;
	std::string currentSatalite = "Moon";


	// Title Screen //////////
	TitleScreen titleScreen;

	// Level Select //////////
	LevelSelect levelSelect;

	// Level_1 //////////
	Level_1UI level_1UI;
	static constexpr int level_1LaunchCounterMax = 2;
	static constexpr float level_1MinSpawnDistFromSun = 300.0f;

	// Level_2 //////////
	Level_2UI level_2UI;
	static constexpr int level_2LaunchCounterMax = 2;
	static constexpr float level_2MinSpawnDistFromSun = 600.0f;

	// Level_3 //////////
	Level_3UI level_3UI;
	static constexpr int level_3LaunchCounterMax = 5;

	// Sandbox //////////
	SandboxUI sandboxUI;

	// Universal Objects //////////
	FrameTimer ft;
	Counter frameCounter;
	Counter launchCounter;
	std::map<std::string, float> radiusMap;
	std::map<std::string, sf::Texture> textureMap;
	std::map<int, std::string> starIndexMap;
	std::map<int, std::string> planetIndexMap;
	std::map<int, std::string> sataliteIndexMap;
	std::map<int, std::string> cometIndexMap;
	std::map<int, std::string> weaponIndexMap;
	std::vector<SpaceObj> spaceObjArray;
	std::vector<SpawnObj> spawnObjArray;
	Line launchLine;
	PauseUI pauseUI;
	PostGameUI postGameUI;
	PanZoom panZoom;
	SpawnCircle spawnCircle;
	TargetCircle targetCircle;
	SpawnRectangle spawnRectangle;
	Score score;


public:
	// Window
	sf::RenderWindow* window;

	// Constructor / Destructor
	Game();
	~Game();

	//Accessors
	const bool running() const;

	// Functions
	void resetSpaceObjArray(std::string centreObj, std::string centreObjType);
	void updateAllowInput();
	void updateAllowInputUI();
	void assignTexture(std::string fileName, std::string mapName);
	std::string randomSpaceObj(std::map<int, std::string> indexMap_in) const;
	void pollEvents();
	void update();
	void render();

	// Pause
	void updatePause();
	void renderPause();

	// Post Game
	void updatePostGame();
	void renderPostGame();

	// Title Screen Functions
	void updateTitleScreen();
	void renderTitleScreen();

	// Level Select Functions
	void updateLevelSelect();
	void renderLevelSelect();

	// Level_1 Functions
	void updateLevel_1();
	void renderLevel_1();
	void resetLevel_1();

	// Level_2 Functions
	void updateLevel_2();
	void renderLevel_2();
	void resetLevel_2();

	// Level_3 Functions
	void updateLevel_3();
	void renderLevel_3();
	void resetLevel_3();

	// Sandbox Functions
	void updateSandbox();
	void renderSandbox();
	void resetSandbox();
};