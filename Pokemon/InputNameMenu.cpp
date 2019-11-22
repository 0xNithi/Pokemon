#include "stdafx.h"
#include "InputNameMenu.h"

InputNameMenu::InputNameMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	// Init background

	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	// Init container

	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 1.5f,
			static_cast<float>(window.getSize().y) - 100.f
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		50.f
	);

	// Init text

	this->inputText.setFont(font);
	this->inputText.setFillColor(sf::Color(255, 255, 255, 200));
	this->inputText.setCharacterSize(60);
	this->inputText.setString("Enter your name!");
	this->inputText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2 - this->inputText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 40.f
	);

	this->showText.setFont(font);
	this->showText.setFillColor(sf::Color(255, 255, 255, 200));
	this->showText.setCharacterSize(50);
}

InputNameMenu::~InputNameMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& InputNameMenu::getButtons()
{
	return this->buttons;
}

const bool InputNameMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void InputNameMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 350.f;
	float height = 75.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, 50,
		sf::Color(70, 70, 70, 200), sf::Color(40, 40, 40, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 200), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
}

void InputNameMenu::update(const sf::Vector2i mousePosWindow, const std::string name)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}

	if (this->myClock.getElapsedTime() >= sf::milliseconds(500))
	{
		this->myClock.restart();
		this->showCursor = !showCursor;
	}

	std::stringstream ss;

	if (showCursor)
		ss << name << "_";
	else
		ss << name << " ";

	this->showText.setString(ss.str());
	this->showText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2 - this->showText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 200.f
	);
}

void InputNameMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->inputText);
	target.draw(this->showText);
}
