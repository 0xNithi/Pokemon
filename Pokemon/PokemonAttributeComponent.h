#ifndef POKEMONATTRIBUTECOMPONENT_H
#define POKEMONATTRIBUTECOMPONENT_H

class PokemonAttributeComponent
{
public:

	unsigned id;
	bool buddy;

	// Level

	unsigned level;
	unsigned int exp;
	unsigned int expNext;
	unsigned attributePoints;

	// Stats

	int hp;
	int hpMax;
	unsigned attack;
	unsigned defense;
	unsigned spAtk;
	unsigned spDef;
	unsigned speed;

	// Constructors / Destructors

	PokemonAttributeComponent(unsigned id ,unsigned level);
	virtual ~PokemonAttributeComponent();

	// Functions

	void loseHP(const int hp);
	void gainHP(const int hp);
	void gainExp(const int exp);

	void updateStats(const bool reset);
	void updateLevel();
	void update();
};

#endif