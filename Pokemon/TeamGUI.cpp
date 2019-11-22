#include "stdafx.h"
#include "TeamGUI.h"

void TeamGUI::initProfile()
{
	for (size_t i = 0; i < this->team->getMaxMember(); i++)
	{
		this->profileBackground.setSize(sf::Vector2f(200.f, 60.f));
		this->profileBackground.setFillColor(sf::Color(255, 255, 255, 155));

		this->profilePokemon.setSize(sf::Vector2f(80.f, 80.f));

		this->profileText.setFont(this->font);
		this->profileText.setCharacterSize(15);
	}
}

TeamGUI::TeamGUI(Team* team, sf::Font& font)
{
	this->team = team;

	this->font = font;

	this->initProfile();
}

TeamGUI::~TeamGUI()
{
}

void TeamGUI::update(const float& dt)
{
}

void TeamGUI::render(sf::RenderTarget& target)
{
	for (size_t i = 0; i < this->team->getMaxMember(); i++)
	{
		if (this->team->pokemonArray[i]->getPokemonAttributeComponent()->buddy)
		{
			if (!this->profileTexture.loadFromFile("Resources/Images/UI/pokemon_profile_selected.png"))
			{
				throw "ERROR::TEAMGUI::FAILED_TO_LOAD_POKEMON_PROFILE";
			}
		}
		else
		{
			if (!this->profileTexture.loadFromFile("Resources/Images/UI/pokemon_profile.png"))
			{
				throw "ERROR::TEAMGUI::FAILED_TO_LOAD_POKEMON_PROFILE";
			}
		}
		this->profileBackground.setTexture(&this->profileTexture);
		this->profileBackground.setPosition(15.f, 180.f + 80.f * i);

		std::stringstream ss;
		ss << "Resources/Images/Picons/" << this->team->pokemonArray[i]->getPokemonAttributeComponent()->id << "_1.png";
		if (!this->profilePokemonTexture.loadFromFile(ss.str()))
		{
			throw "ERROR::TEAMGUI::FAILED_TO_LOAD_POKEMON_PROFILE";
		}
		this->profilePokemon.setPosition(15.f, 160.f + 80.f * i);
		this->profilePokemon.setTexture(&this->profilePokemonTexture);

		ss.str("");
		ss << "Level " << std::setfill(' ') << std::setw(2) << this->team->pokemonArray[i]->getPokemonAttributeComponent()->level << "\n" 
			<< "Hp " << std::setfill(' ') << std::setw(5) << this->team->pokemonArray[i]->getPokemonAttributeComponent()->hp;

		this->profileText.setPosition(95.f, 190.f + 80.f * i);
		this->profileText.setString(ss.str());


		target.draw(this->profileBackground);
		target.draw(this->profileText);
		target.draw(this->profilePokemon);
	}
}
