#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:

	// Variables

	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	// Initializer functions

	void initVariables();
	void initGraphicsSettings();
	void initStateDate();
	void initWindow();
	void initKeys();
	void initStates();

public:

	// Constructors/Destructors

	Game();
	virtual ~Game();

	// Functions

	// Regular

	void endApplication();

	// Update

	void updateDt();
	void updateSFMLEvents();
	void update();

	// Render

	void render();

	// Core

	void run();
};

#endif