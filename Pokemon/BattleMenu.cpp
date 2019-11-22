#include "stdafx.h"
#include "BattleMenu.h"

BattleMenu::BattleMenu(Team* team, sf::Font& font, sf::RenderWindow& window, bool gymBattle)
{
	this->team = team;

	this->font = font;

	this->window = &window;

	this->blink.setFillColor(sf::Color::White);
	this->blink.setSize(sf::Vector2f(this->window->getSize()));

	if (!this->battleTexture.loadFromFile("Resources/Images/Backgrounds/battlemenu.png"))
	{
		throw "ERROR::BATTLEMENU::FAILED_TO_LOAD_BATTLE_TEXTURE";
	}
	this->battleBackground.setTexture(&this->battleTexture);
	this->battleBackground.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y - this->window->getSize().y / 4));

	if (!this->uiBackgroundTexture.loadFromFile("Resources/Images/UI/battle_text.png"))
	{
		throw "ERROR::BATTLEMENU::FAILED_TO_LOAD_UI_BACKGROUND_TEXTURE";
	}
	this->uiBackground.setTexture(&this->uiBackgroundTexture);
	this->uiBackground.setPosition(0.f, this->battleBackground.getGlobalBounds().height);
	this->uiBackground.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y - this->battleBackground.getGlobalBounds().height));

	float x = this->uiBackground.getGlobalBounds().left + this->uiBackground.getGlobalBounds().width / 1.4;
	float y = this->uiBackground.getGlobalBounds().top + 40;

	srand(time(NULL));
	std::stringstream ss;

	for (size_t i = 0; i < this->team->getMaxMember(); i++)
	{
		if (this->team->pokemonArray[i]->getPokemonAttributeComponent()->buddy)
		{
			ss << "Resources/Images/Sprites/Pokemon/Back/" << this->team->pokemonArray[i]->getPokemonAttributeComponent()->id << ".png";

			if (!this->buddy.loadFromFile(ss.str()))
			{
				throw "ERROR::BATTLEMENU::FAILED_TO_LOAD_BUDDY_TEXTURE";
			}
			this->buddyShape.setTexture(&this->buddy);
			this->buddyShape.setSize(sf::Vector2f(128.f * 2.5, 128.f * 2.5));
			this->buddyShape.setPosition(this->window->getSize().x / 8, this->window->getSize().y - this->window->getSize().y / 4 - this->buddyShape.getGlobalBounds().width);

			if (!this->buddyDetail.loadFromFile("Resources/Images/UI/battle_pokemon_bar.png"))
			{
				throw "ERROR::BATTLEMENU::FAILED_TO_LOAD_BUDDY_DETAIL_TEXTURE";
			}
			this->buddyDetailShape.setTexture(&this->buddyDetail);
			this->buddyDetailShape.setSize(sf::Vector2f(208.f * 2.5, 74.f * 2.5));
			this->buddyDetailShape.setPosition(this->window->getSize().x / 2 + this->window->getSize().x / 20, this->battleBackground.getGlobalBounds().height - this->buddyDetailShape.getGlobalBounds().height);

			this->buddyText.setFont(this->font);
			this->buddyText.setCharacterSize(40);
			this->buddyText.setFillColor(sf::Color::Black);
			this->buddyText.setPosition(this->window->getSize().x / 2 + this->window->getSize().x / 8, this->battleBackground.getGlobalBounds().height - this->buddyDetailShape.getGlobalBounds().height / 1.25);

			this->enemyPokemon = new Pokemon((rand() % 150 + 1), (gymBattle ? 30 : (this->team->pokemonArray[i]->getPokemonAttributeComponent()->level + rand() % 6 - 5)));

			this->buttons["SKILL3"] = new gui::Button(
				x, y + 60, 155.f, 50.f,
				&this->font, "Heal", 20,
				sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(255, 167, 28, (this->team->pokemonArray[i]->getPokemonAttributeComponent()->level >= 15) ? 255 : 100), sf::Color(255, 167, 28, (this->team->pokemonArray[i]->getPokemonAttributeComponent()->level >= 15) ? 255 : 100), sf::Color(255, 167, 28, 200)
			);
			this->buttons["SKILL4"] = new gui::Button(
				x + 165, y + 60, 155.f, 50.f,
				&this->font, "Ultimate", 20,
				sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(255, 167, 28, (this->team->pokemonArray[i]->getPokemonAttributeComponent()->level >= 20) ? 255 : 100), sf::Color(255, 167, 28, (this->team->pokemonArray[i]->getPokemonAttributeComponent()->level >= 20) ? 255 : 100), sf::Color(255, 167, 28, 200)
			);
		}
	}

	ss.str("");
	ss << "Resources/Images/Sprites/Pokemon/Front/" << this->enemyPokemon->getPokemonAttributeComponent()->id << ".png";

	if (!this->enemy.loadFromFile(ss.str()))
	{
		throw "ERROR::BATTLEMENU::FAILED_TO_LOAD_ENEMY_TEXTURE";
	}
	this->enemyShape.setTexture(&this->enemy);
	this->enemyShape.setSize(sf::Vector2f(128.f * 2.5, 128.f * 2.5));
	this->enemyShape.setPosition(this->window->getSize().x * 5 / 8, this->window->getSize().y - this->window->getSize().y / 2 - this->enemyShape.getGlobalBounds().width);


	if (!this->enemyDetail.loadFromFile("Resources/Images/UI/battle_enemy_bar.png"))
	{
		throw "ERROR::BATTLEMENU::FAILED_TO_LOAD_ENEMEY_DETAIL_TEXTURE";
	}
	this->enemyDetailShape.setTexture(&this->enemyDetail);
	this->enemyDetailShape.setSize(sf::Vector2f(208.f * 2.5, 74.f * 2.5));
	this->enemyDetailShape.setPosition(this->window->getSize().x / 10, this->battleBackground.getGlobalBounds().height / 2.5f - this->enemyDetailShape.getGlobalBounds().height);

	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(40);
	this->enemyText.setFillColor(sf::Color::Black);
	this->enemyText.setPosition(this->window->getSize().x / 6, this->battleBackground.getGlobalBounds().height / 2.125f - this->enemyDetailShape.getGlobalBounds().height);

	this->buttons["FIGHT"] = new gui::Button(
		x, y, 155.f, 50.f,
		&this->font, "Fight", 24,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
	this->buttons["POKEMON"] = new gui::Button(
		x + 165, y, 155.f, 50.f,
		&this->font, "Pokemon", 24,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
	this->buttons["RUN"] = new gui::Button(
		x, y + 60, 320.f, 50.f,
		&this->font, "Run", 24,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
	this->buttons["EXIT"] = new gui::Button(
		x, y, 320.f, 110.f,
		&this->font, "Exit", 50,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);

	this->buttons["SKILL1"] = new gui::Button(
		x, y, 155.f, 50.f,
		&this->font, "Attack", 20,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
	this->buttons["SKILL2"] = new gui::Button(
		x + 165, y, 155.f, 50.f,
		&this->font, "Counter", 20,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);

	this->buttons["POKEMON1"] = new gui::Button(
		x, y, 155.f, 50.f,
		&this->font, "Bulbasaur", 18,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
	this->buttons["POKEMON2"] = new gui::Button(
		x + 165, y, 155.f, 50.f,
		&this->font, "Charmander", 18,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
	this->buttons["POKEMON3"] = new gui::Button(
		x, y + 60, 155.f, 50.f,
		&this->font, "Squirtle", 18,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
	this->buttons["BACK"] = new gui::Button(
		x + 165, y + 60, 155.f, 50.f,
		&this->font, "Back", 18,
		sf::Color(70, 70, 70, 255), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 255), sf::Color(255, 167, 28, 200)
	);
}

BattleMenu::~BattleMenu()
{
	delete this->enemyPokemon;

	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

const bool BattleMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

const bool BattleMenu::isFightMenu()
{
	return this->fightMenu;
}

const bool BattleMenu::isSelectPokemon()
{
	return this->selectPokemon;
}

const bool BattleMenu::getEnd()
{
	return this->isEnd;
}

void BattleMenu::setFightMenu(const bool status)
{
	this->fightMenu = status;
}

void BattleMenu::setSelectPokemon(const bool status)
{
	this->selectPokemon = status;
}

void BattleMenu::setPokemon(unsigned id)
{
	for (size_t i = 0; i < this->team->getMaxMember(); i++)
		if (this->team->pokemonArray[i]->getPokemonAttributeComponent()->buddy)
			this->team->pokemonArray[i]->getPokemonAttributeComponent()->buddy = !this->team->pokemonArray[i]->getPokemonAttributeComponent()->buddy;
	this->team->pokemonArray[id]->getPokemonAttributeComponent()->buddy = true;
}

void BattleMenu::attack(const unsigned value)
{
	this->enemyPokemon->getPokemonAttributeComponent()->loseHP(value - this->enemyPokemon->getPokemonAttributeComponent()->defense / 2);
}

void BattleMenu::heal(const unsigned value)
{
	for (size_t i = 0; i < this->team->getMaxMember(); i++)
		if (this->team->pokemonArray[i]->getPokemonAttributeComponent()->buddy)
			this->team->pokemonArray[i]->getPokemonAttributeComponent()->gainHP(value);
}

void BattleMenu::enemySkill()
{

	unsigned skill = rand() % (this->enemyPokemon->getPokemonAttributeComponent()->level >= 20 ? 4 : this->enemyPokemon->getPokemonAttributeComponent()->level >= 15 ? 3 : 2);

	for (size_t i = 0; i < this->team->getMaxMember(); i++)
	{
		if (this->team->pokemonArray[i]->getPokemonAttributeComponent()->buddy && this->enemyPokemon->getPokemonAttributeComponent()->hp)
		{
			if (skill == 0)
			{
				this->team->pokemonArray[i]->getPokemonAttributeComponent()->loseHP(this->enemyPokemon->getPokemonAttributeComponent()->attack - this->team->pokemonArray[i]->getPokemonAttributeComponent()->defense / 2);
				this->team->pokemonArray[i]->playSound("ATTACK");

				this->isEnemyAttack = true;
			}
			else if (skill == 1)
			{
				this->team->pokemonArray[i]->getPokemonAttributeComponent()->loseHP(this->enemyPokemon->getPokemonAttributeComponent()->attack * (rand() % 2 + 1) - this->team->pokemonArray[i]->getPokemonAttributeComponent()->defense / 2);
				this->team->pokemonArray[i]->playSound("COUNTER");

				this->isEnemyAttack = true;
			}
			else if (skill == 2)
			{
				this->enemyPokemon->getPokemonAttributeComponent()->gainHP(this->enemyPokemon->getPokemonAttributeComponent()->hpMax / 3);
				this->team->pokemonArray[i]->playSound("HEAL");
			}
			else if (skill == 3)
			{
				srand(time(NULL));

				this->team->pokemonArray[i]->getPokemonAttributeComponent()->loseHP(this->enemyPokemon->getPokemonAttributeComponent()->attack * (rand() % 3 + 1) - this->team->pokemonArray[i]->getPokemonAttributeComponent()->defense / 2);
				this->team->pokemonArray[i]->playSound("ULTIMATE");

				this->isEnemyAttack = true;
			}

			this->myClock.restart();
		}
	}
}

void BattleMenu::update(const sf::Vector2i mousePosWindow)
{
	unsigned allPokemonHp = 0;
	std::stringstream ss;
	for (size_t i = 0; i < this->team->getMaxMember(); i++)
	{
		allPokemonHp += this->team->pokemonArray[i]->getPokemonAttributeComponent()->hp;

		if (this->team->pokemonArray[i]->getPokemonAttributeComponent()->buddy)
		{
			ss << "Level : " << this->team->pokemonArray[i]->getPokemonAttributeComponent()->level << "\n"
				<< "Hp : " << this->team->pokemonArray[i]->getPokemonAttributeComponent()->hp;
			this->buddyText.setString(ss.str()); 

			if (this->team->pokemonArray[i]->getPokemonAttributeComponent()->hp == 0)
			{
				this->fightMenu = false;
			}

			ss.str("");
			ss << "Resources/Images/Sprites/Pokemon/Back/" << this->team->pokemonArray[i]->getPokemonAttributeComponent()->id << ".png";

			if (!this->buddy.loadFromFile(ss.str()))
			{
				throw "ERROR::BATTLEMENU::FAILED_TO_LOAD_BUDDY_TEXTURE";
			}
			this->buddyShape.setTexture(&this->buddy);
		}
	}

	ss.str("");
	ss << "Level : " << this->enemyPokemon->getPokemonAttributeComponent()->level << "\n"
		<< "Hp : " << this->enemyPokemon->getPokemonAttributeComponent()->hp;

	this->enemyText.setString(ss.str());

	for (auto& it : this->buttons)
	{
		if (!this->isEnd)
		{
			if (this->fightMenu)
			{
				if (it.first != "FIGHT" && it.first != "POKEMON" && it.first != "RUN" && it.first != "EXIT" && it.first != "POKEMON1" && it.first != "POKEMON2" && it.first != "POKEMON3" && it.first != "BACK")
					it.second->update(mousePosWindow);
			}
			else if (this->selectPokemon)
			{
				if (it.first != "FIGHT" && it.first != "POKEMON" && it.first != "RUN" && it.first != "EXIT" && it.first != "SKILL1" && it.first != "SKILL2" && it.first != "SKILL3" && it.first != "SKILL4")
					it.second->update(mousePosWindow);
			}
			else
			{
				if (it.first != "EXIT" && it.first != "SKILL1" && it.first != "SKILL2" && it.first != "SKILL3" && it.first != "SKILL4" && it.first != "POKEMON1" && it.first != "POKEMON2" && it.first != "POKEMON3" && it.first != "BACK")
					it.second->update(mousePosWindow);
			}

		}
		else
		{
			if (it.first == "EXIT")
				it.second->update(mousePosWindow);
		}
	}

	if (!this->isEnd && (this->enemyPokemon->getPokemonAttributeComponent()->hp == 0 || allPokemonHp == 0))
	{
		if (this->enemyPokemon->getPokemonAttributeComponent()->hp == 0)
		{
			for (size_t i = 0; i < this->team->getMaxMember(); i++)
			{
				if (this->team->pokemonArray[i]->getPokemonAttributeComponent()->buddy)
				{
					this->team->pokemonArray[i]->getPokemonAttributeComponent()->gainExp(this->enemyPokemon->getPokemonAttributeComponent()->expNext);
				}
			}
		}

		this->fightMenu = false;
		this->isEnd = true;

		sf::sleep(sf::seconds(0.2f));
	}
}

void BattleMenu::render(sf::RenderTarget& target)
{
	target.draw(this->battleBackground);
	target.draw(this->uiBackground);
	target.draw(this->buddyShape);
	target.draw(this->buddyDetailShape);
	target.draw(this->buddyText);
	target.draw(this->enemyShape);
	target.draw(this->enemyDetailShape);
	target.draw(this->enemyText);

	for (auto& it : this->buttons)
	{
		if (!this->isEnd)
		{
			if (this->fightMenu)
			{
				if (it.first != "FIGHT" && it.first != "POKEMON" && it.first != "RUN" && it.first != "EXIT" && it.first != "POKEMON1" && it.first != "POKEMON2" && it.first != "POKEMON3" && it.first != "BACK")
					it.second->render(target);
			}
			else if (this->selectPokemon)
			{
				if (it.first != "FIGHT" && it.first != "POKEMON" && it.first != "RUN" && it.first != "EXIT" && it.first != "SKILL1" && it.first != "SKILL2" && it.first != "SKILL3" && it.first != "SKILL4")
				{
					it.second->render(target);
				}
			}
			else
			{
				if (it.first != "EXIT" && it.first != "SKILL1" && it.first != "SKILL2" && it.first != "SKILL3" && it.first != "SKILL4" && it.first != "POKEMON1" && it.first != "POKEMON2" && it.first != "POKEMON3" && it.first != "BACK")
					it.second->render(target);
			}
		}
		else
		{
			if (it.first == "EXIT")
				it.second->render(target);
		}
	}

	if (this->myClock.getElapsedTime() >= sf::milliseconds(50))
	{
		this->myClock.restart();

		if (this->isEnemyAttack)
		{
			this->isEnemyAttack = false;
		}
	}

	if (this->isEnemyAttack)
	{
		target.draw(this->blink);
	}
}
