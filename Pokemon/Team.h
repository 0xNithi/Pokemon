#ifndef TEAM_H
#define TEAM_H

#include "Pokemon.h"

class Pokemon;

class Team
{
private:

	unsigned maxMenber;

	void initialize();
	void freeMemory();

public:

	Pokemon** pokemonArray;

	Team(unsigned maxMenber);
	virtual ~Team();

	// Functions

	const unsigned getMaxMember() const;

	void add(Pokemon* pokemon, unsigned slot);
};

#endif