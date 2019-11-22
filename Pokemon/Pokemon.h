#ifndef POKEMON_H
#define POKEMON_H

#include "Entity.h"

class Entity;

class Pokemon :
	public Entity
{
private:

	// Variables

	sf::Texture buddyTexture;

public:

	Pokemon(unsigned id, unsigned level);
	virtual ~Pokemon();

	// Accessors

	PokemonAttributeComponent* getPokemonAttributeComponent();

	// Functions

	void playSound(std::string key);
	void updateAnimation(const float& dt);
	void update(const float& dt);

	void render(sf::RenderTarget& target);
};

#endif