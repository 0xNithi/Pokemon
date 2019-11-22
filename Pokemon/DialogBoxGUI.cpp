#include "stdafx.h"
#include "DialogBoxGUI.h"

DialogBoxGUI::DialogBoxGUI(std::string message, sf::Font& font, sf::RenderWindow& window)
{
	this->window = &window;
	this->font = font;

	this->index = 0;

	this->message = message;
	this->messageText.setFont(this->font);
	this->messageText.setPosition(50.f, this->window->getSize().y * 3 / 4 + 50);

	this->dialogBox.setFillColor(sf::Color::Black);
	this->dialogBox.setOutlineColor(sf::Color::White);
	this->dialogBox.setOutlineThickness(-5.f);
	this->dialogBox.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y / 4));
	this->dialogBox.setPosition(0.f, this->window->getSize().y * 3 / 4);

}

DialogBoxGUI::~DialogBoxGUI()
{
}

void DialogBoxGUI::update()
{
	if (this->myClock.getElapsedTime() >= sf::milliseconds(20) && this->index <= this->message.length())
	{
		this->index++;
		this->myClock.restart();
	}
	
	this->messageText.setString(this->message.substr(0, this->index));
}

void DialogBoxGUI::render(sf::RenderTarget& target)
{
	target.draw(this->dialogBox);
	target.draw(this->messageText);
}
