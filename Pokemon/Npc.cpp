#include "stdafx.h"
#include "Npc.h"

void Npc::initComponents(float x, float y, sf::Texture& texture_sheet)
{
	this->setTexture(this->sprite, texture_sheet);
	this->setPosition(this->sprite, x, y);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 0.f, 0, 0, 0, 0, 28, 40);
}

Npc::Npc(float x, float y, sf::Texture& texture_sheet)
{
	this->initComponents(x, y, texture_sheet);
}

Npc::~Npc()
{
}

void Npc::update(const float& dt)
{
}

void Npc::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
