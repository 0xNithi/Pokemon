#include "stdafx.h"
#include "PokemonAttributeComponent.h"

PokemonAttributeComponent::PokemonAttributeComponent(unsigned id ,unsigned level)
{
	this->buddy = false;
	this->id = id;
	this->level = 0;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 7 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	this->attributePoints = rand() % 5 + 2;

	for (int i = 0; i < level; i++)
	{
		this->gainExp(this->expNext);
	}

	this->updateLevel();
	this->updateStats(true);
}

PokemonAttributeComponent::~PokemonAttributeComponent()
{
}

void PokemonAttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

void PokemonAttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void PokemonAttributeComponent::gainExp(const int exp)
{
	this->exp += exp;

	this->updateLevel();
}

void PokemonAttributeComponent::updateStats(const bool reset)
{
	this->hpMax = this->attributePoints * 12;
	this->attack = this->attributePoints * 4;
	this->defense = this->attributePoints * 3;
	this->spAtk = this->attributePoints * 7;
	this->spDef = this->attributePoints * 8;
	this->speed = this->attributePoints * 7;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void PokemonAttributeComponent::updateLevel()
{
	if (this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
		++this->attributePoints;

		if (this->level == 20)
		{
			this->id++;
			this->attributePoints += this->attributePoints / 2;
		}
		if (this->level == 30)
		{
			this->id++;
			this->attributePoints += this->attributePoints / 2;
		}

		this->updateStats(true);
	}
}

void PokemonAttributeComponent::update()
{
	this->updateLevel();
}
