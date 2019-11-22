#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Entity;

class Player :
	public Entity
{
private:

	// Variables

	unsigned long coins;

	// Initializer functions

	void initVariables();
	void initComponents(float x, float y, sf::Texture& texture_sheet);

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	// Accessors

	const unsigned long& getCoins() const;
	void setCoins(int value);

	// Functions

	void playHeal();
	void updateAnimation(const float& dt);
	void updateSoundEffect(const float& dt);
	void update(const float& dt);

	void render(sf::RenderTarget& target);
};

#endif