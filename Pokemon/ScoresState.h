#ifndef SCORESSTATE_H
#define SCORESSTATE_H

#include "State.h"
#include "Gui.h"

class ScoresState :
	public State
{
private:

	// Variebles

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::RectangleShape scoreBackground;
	sf::Font font;
	sf::Text score;

	std::map<std::string, gui::Button*> buttons;
	std::map<unsigned, std::string> scores;

	// Functions

	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initText();

public:
	ScoresState(StateData* state_data);
	virtual ~ScoresState();

	// Accessors

	// Functions

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

#endif