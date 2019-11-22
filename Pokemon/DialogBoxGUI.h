#ifndef DIALOGBOXGUI_H
#define DIALOGBOXGUI_H

class DialogBoxGUI
{
public:

	sf::Font font;
	sf::RenderWindow* window;

	unsigned index;

	std::string message;
	sf::Text messageText;
	sf::RectangleShape dialogBox;

	sf::Clock myClock;

	DialogBoxGUI(std::string message, sf::Font& font, sf::RenderWindow& window);
	virtual ~DialogBoxGUI();

	void update();
	void render(sf::RenderTarget& target);
};

#endif