#include "stdafx.h"
#include "SettingsState.h"

// Initializer functions

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
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

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/joystix monospace.ttf"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_FONT";
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
{
	this->buttons["BACK"] = new gui::Button(
		1500.f, 905.f, 250.f, 50.f,
		&this->font, "Back", 40,
		sf::Color(70, 70, 70, 200), sf::Color(40, 40, 40, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);

	this->buttons["APPLY"] = new gui::Button(
		1200.f, 905.f, 250.f, 50.f,
		&this->font, "Apply", 40,
		sf::Color(70, 70, 70, 200), sf::Color(40, 40, 40, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropdownLists["RESOLUTION"] = new gui::DropDownList(800, 450, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);

	this->optionsText.setPosition(sf::Vector2f(100.f, 100.f));

	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntializsing"
	);
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	for (auto it = this->dropdownLists.begin(); it != this->dropdownLists.end(); ++it)
	{
		delete it->second;
	}
}

// Functions

void SettingsState::updateInput(const float& dt)
{
}

void SettingsState::updateGui(const float& dt)
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

	// Apply selected settings

	if (this->buttons["APPLY"]->isPressed())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->dropdownLists["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}

	// Dropdown lists

	for (auto& it : this->dropdownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}

	// Dropdown lists functionality
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropdownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	//sf::Text mouseText;
	//mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mousePosView.x << " " << this->mousePosView.y;
	//mouseText.setString(ss.str());

	//target->draw(mouseText);

}
