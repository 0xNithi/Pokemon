#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "InputNameMenu.h"
#include "BattleMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Team.h"
#include "TeamGUI.h"
#include "DialogBoxGUI.h"

class GameState :
	public State
{
private:

	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;
	InputNameMenu* imenu;
	BattleMenu* bmenu;

	Player* player;
	PlayerGUI* playerGUI;
	Team* team;
	TeamGUI* teamGUI;

	DialogBoxGUI* dialogBoxGUI;
	sf::Texture texture;

	TileMap* tileMap;

	std::map<std::string, Pokemon*> pokemons;

	Npc* nurse;
	Npc* doctor;
	Npc* gymLeader;

	sf::RectangleShape CreditScreen;
	sf::Text CreditText;

	std::string trainerName;

	sf::Clock myClock;

	bool isInputName = true;

	bool isBattle = false;
	bool gymBattle = false;
	bool playerLose = false;
	bool healUsed = false;
	bool ultimateUsed = false;

	unsigned gymCount = 0;

	unsigned quest;
	unsigned questProgress;
	bool isQuest = false;
	bool isRewarded;

	bool isCheatMode = false;

	// Functions

	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTexture();
	void initPauseMenu();
	void initInputNameMenu();
	void initPlayer();
	void initPlayerGUI();
	void initNpc();
	void initTeam();
	void initTeamGUI();
	void initTileMap();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	// Functions

	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updateTeamBuddy(const float& dt);
	void updatePauseMenuButtons();
	void updateBattleMenuButtons();
	void updateInputNameMenuButtons();
	void updateTileMap(const float& dt);
	void updateDialog();
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif
