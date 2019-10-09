#include "MainMenuState.h"

// Initializer functions

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/joystix monospace.ttf"))
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
	this->buttons["GAME_STATE"] = new Button(
		775, 480, 400, 75,
		&this->font, "New Game", 50,
		sf::Color(70, 70, 70, 200),
		sf::Color(40, 40, 40, 250),
		sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200),
		sf::Color(255, 167, 28, 255),
		sf::Color(255, 167, 28, 200)
	);

	this->buttons["SETTINGS"] = new Button(
		775, 580, 400, 75,
		&this->font, "Settings", 50,
		sf::Color(70, 70, 70, 200),
		sf::Color(40, 40, 40, 250),
		sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200),
		sf::Color(255, 167, 28, 255),
		sf::Color(255, 167, 28, 200)
	);

	this->buttons["EDITOR_STATE"] = new Button(
		775, 680, 400, 75,
		&this->font, "Editor", 50,
		sf::Color(70, 70, 70, 200),
		sf::Color(40, 40, 40, 250),
		sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200),
		sf::Color(255, 167, 28, 255),
		sf::Color(255, 167, 28, 200)
	);

	this->buttons["EXIT_STATE"] = new Button(
		775, 880, 400, 75,
		&this->font, "Quit", 50,
		sf::Color(70, 70, 70, 200),
		sf::Color(40, 40, 40, 250),
		sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200),
		sf::Color(255, 167, 28, 255),
		sf::Color(255, 167, 28, 200)
	);
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
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
		it.second->update(this->mousePosView);
	}

	// New Game

	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
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

void MainMenuState::renderButtons(sf::RenderTarget* target)
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

	this->renderButtons(target);

	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);

}
