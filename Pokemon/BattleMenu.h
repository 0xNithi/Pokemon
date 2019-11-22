#ifndef BATTLEMENU_H
#define BATTLEMENU_H

#include "Team.h"
#include "Gui.h"

class Team;

class BattleMenu
{
private:

	Team* team;
	sf::RenderWindow* window;
	sf::Font font;

	sf::Texture battleTexture;
	sf::RectangleShape battleBackground;

	sf::Texture uiBackgroundTexture;
	sf::RectangleShape uiBackground;

	sf::Text buddyText;
	sf::Texture buddy;
	sf::Texture buddyDetail;
	sf::RectangleShape buddyShape;
	sf::RectangleShape buddyDetailShape;

	sf::Text enemyText;
	sf::Texture enemy;
	sf::Texture enemyDetail;
	sf::RectangleShape enemyShape;
	sf::RectangleShape enemyDetailShape;

	sf::RectangleShape blink;
	
	std::map<std::string, gui::Button*> buttons;

	sf::Clock myClock;

	bool isEnd = false;
	bool fightMenu = false;
	bool selectPokemon = false;

	bool isEnemyAttack = false;

public:
	Pokemon* enemyPokemon;

	BattleMenu(Team* team, sf::Font& font, sf::RenderWindow& window, bool gymBattle = false);
	virtual ~BattleMenu();

	// Functions

	const bool isButtonPressed(const std::string key);
	const bool isFightMenu();
	const bool isSelectPokemon();
	const bool getEnd();

	void setFightMenu(const bool status);
	void setSelectPokemon(const bool status);
	void setPokemon(unsigned id);
	void attack(const unsigned value);
	void heal(const unsigned value);
	void enemySkill();

	void update(const sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget & target);
};
#endif