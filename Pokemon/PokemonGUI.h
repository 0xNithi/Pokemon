#ifndef POKEMONGUI
#define POKEMONGUI

#include "Pokemon.h"

class Pokemon;

class PokemonGUI
{
private:

	void initProfile(sf::Sprite& sprite);

public:
	
	PokemonGUI(Pokemon* pokemon, sf::Font& font, sf::Sprite& sprite);
	virtual ~PokemonGUI();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif