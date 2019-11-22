#ifndef NPC_H
#define NPC_H

#include "Entity.h"

class Entity;

class Npc :
	public Entity
{
private:

	// Initializer functions

	void initComponents(float x, float y, sf::Texture& texture_sheet);

public:
	Npc(float x, float y, sf::Texture& texture_sheet);
	virtual ~Npc();

	// Functions

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif