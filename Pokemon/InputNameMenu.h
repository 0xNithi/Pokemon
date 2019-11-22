#ifndef INPUTNAMEMENU_H
#define INPUTNAMEMENU_H

#include "Gui.h"

class Gui;

class InputNameMenu
{
private:

	sf::Font& font;
	sf::Text inputText;
	sf::Text showText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	sf::Clock myClock;
	bool showCursor = false;

public:

	InputNameMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~InputNameMenu();

	std::map<std::string, gui::Button*>& getButtons();

	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2i mousePosWindow, const std::string name);
	void render(sf::RenderTarget& target);
};

#endif