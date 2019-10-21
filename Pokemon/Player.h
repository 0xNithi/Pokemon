#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :
	public Entity
{
private:

	// Variables

	float soundTimer;
	float timer;

	sf::SoundBuffer buffer;
	sf::Sound walkSound;

	// Initializer functions

	void initVariables();
	void initComponents();
	void initSoundEffects();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	// Functions

	void updateAnimation(const float& dt);
	void updateSound(const float& dt);
	void update(const float& dt);

	void render(sf::RenderTarget& target);
};

#endif