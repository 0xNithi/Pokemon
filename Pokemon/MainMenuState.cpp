#include "stdafx.h"
#include "MainMenuState.h"

// Initializer functions

void MainMenuState::initVariables()
{
	this->stateData->setMusic();
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/mainmenu.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/joystix monospace.ttf"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_FONT";
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initButton()
{
	this->buttons["GAME_STATE"] = new gui::Button(
		this->window->getSize().x / 2.f - 200.f, 480.f, 400.f, 75.f,
		&this->font, "New Game", 50,
		sf::Color(70, 70, 70, 200), sf::Color(40, 40, 40, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		this->window->getSize().x / 2.f - 200.f, 580.f, 400.f, 75.f,
		&this->font, "Settings", 50,
		sf::Color(70, 70, 70, 200), sf::Color(40, 40, 40, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);

	this->buttons["EDITOR_STATE"] = new gui::Button(
		this->window->getSize().x / 2.f - 200.f, 680.f, 400.f, 75.f,
		&this->font, "Editor", 50,
		sf::Color(70, 70, 70, 200), sf::Color(40, 40, 40, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);

	this->buttons["EXIT_STATE"] = new gui::Button(
		this->window->getSize().x / 2.f - 200.f, 880.f, 400.f, 75.f,
		&this->font, "Quit", 50,
		sf::Color(70, 70, 70, 200), sf::Color(40, 40, 40, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButton();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons()
{
	// Update all the buttons in the state and handles their functionlaity

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// New Game

	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
		this->stateData->setMusic("Resources/Audios/Music/gamestate.ogg");
	}

	// Settings

	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	// Editor

	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	// Quit the game

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);
}
