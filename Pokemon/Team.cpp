#include "stdafx.h"
#include "Team.h"

void Team::initialize()
{
	this->pokemonArray = new Pokemon * [this->maxMenber];

	for (size_t i = 0; i < this->maxMenber; i++)
	{
		this->pokemonArray[i] = NULL;
	}
}

void Team::freeMemory()
{
	for (size_t i = 0; i < this->maxMenber; i++)
	{
		delete this->pokemonArray[i];
	}

	delete[] this->pokemonArray;
}

Team::Team(unsigned maxMenber)
{
	this->maxMenber = maxMenber;

	this->initialize();
}

Team::~Team()
{
	this->freeMemory();
}

//Functions

const unsigned Team::getMaxMember() const
{
	return this->maxMenber;
}

void Team::add(Pokemon* pokemon, unsigned slot)
{
	if (slot < this->maxMenber && this->pokemonArray[slot] == NULL)
	{
		this->pokemonArray[slot] = pokemon;
	}
}