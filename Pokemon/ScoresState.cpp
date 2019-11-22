#include "stdafx.h"
#include "ScoresState.h"

// Initializer functions

void ScoresState::initVariables()
{
}

void ScoresState::initBackground()
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

	this->scoreBackground.setFillColor(sf::Color(0, 0, 0, 150));
	this->scoreBackground.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x / 1.4),
			static_cast<float>(this->window->getSize().y / 1.75)
		)
	);
	this->scoreBackground.setPosition(sf::Vector2f(this->window->getSize().x / 2 - this->scoreBackground.getGlobalBounds().width / 2, this->window->getSize().y / 2.5));
}

void ScoresState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/joystix monospace.ttf"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_FONT";
	}
}

void ScoresState::initKeybinds()
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

void ScoresState::initGui()
{
	this->buttons["BACK"] = new gui::Button(
		this->window->getSize().x - 500.f, 650.f, 250.f, 50.f,
		&this->font, "Back", 40,
		sf::Color(70, 70, 70, 200), sf::Color(40, 40, 40, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
}

void ScoresState::initText()
{
	std::string key;
	unsigned num;

	std::ifstream in_file("text.score");

	while (in_file >> key >> num)
	{
		scores[num] = key;
	}

	this->score.setFont(this->font);
	this->score.setCharacterSize(40);
}

ScoresState::ScoresState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

ScoresState::~ScoresState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

// Functions

void ScoresState::updateInput(const float& dt)
{
}

void ScoresState::updateGui(const float& dt)
{
	// Update all the gui element in the state and handles their functionlaity

	// Buttons

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// Button functionality

	// Quit the game

	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	// Dropdown lists functionality
}

void ScoresState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void ScoresState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void ScoresState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	target->draw(this->scoreBackground);

	//std::vector<std::pair<std::string, unsigned> > vec(this->scores.begin(), this->scores.end());

	unsigned i = 0;
	auto it = this->scores.end();
	for (--it; i < 5 && it != this->scores.end(); --it, i++)
	{
		std::stringstream ss;
		ss.imbue(std::locale(""));
		ss << std::setfill(' ') << std::setw(8) << it->second << "\t\t" << std::setfill(' ') << std::setw(6) << it->first << "\n";
		this->score.setString(ss.str());
		this->score.setPosition(sf::Vector2f(this->window->getSize().x / 2 - this->score.getGlobalBounds().width / 2, this->window->getSize().y / 2.25 + 50 * i));
		target->draw(this->score);
	}

	this->renderGui(*target);

	//sf::Text mouseText;
	//mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mousePosView.x << " " << this->mousePosView.y;
	//mouseText.setString(ss.str());

	//target->draw(mouseText);

}
