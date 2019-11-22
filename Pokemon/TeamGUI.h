#ifndef TEAMGUI_H
#define TEAMGUI_H

#include "Team.h"

class Team;

class TeamGUI
{
private:

	Team* team;

	sf::Font font;

	sf::Text profileText;
	sf::Texture profileTexture;
	sf::RectangleShape profileBackground;

	sf::Texture profilePokemonTexture;
	sf::RectangleShape profilePokemon;

	void initProfile();

public:

	TeamGUI(Team* team, sf::Font& font);
	virtual ~TeamGUI();

	// Functions

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif