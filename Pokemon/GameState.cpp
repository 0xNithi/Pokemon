#include "stdafx.h"
#include "GameState.h"

// Initializer functions

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width, 
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0, 
			this->stateData->gfxSettings->resolution.width, 
			this->stateData->gfxSettings->resolution.height
		)
	);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width / 2.f,
			this->stateData->gfxSettings->resolution.height / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Fonts/joystix monospace.ttf"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_FONT";
	}
}

void GameState::initTexture()
{
	if (!this->textures["PLAYER_RED_SHEET"].loadFromFile("Resources/Images/Sprites/Player/red.png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_PLAYER_TEXTURE";
	}
	if (!this->textures["NPC_NURSE_SHEET"].loadFromFile("Resources/Images/Sprites/Npc/nurse.png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_NPC_TEXTURE";
	}
	if (!this->textures["NPC_DOCTOR_SHEET"].loadFromFile("Resources/Images/Sprites/Npc/doctor.png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_NPC_TEXTURE";
	}
	if (!this->textures["NPC_GYM_LEADER_SHEET"].loadFromFile("Resources/Images/Sprites/Npc/gym_leader.png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_NPC_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 600.f, "Quit");
}

void GameState::initInputNameMenu()
{
	this->imenu = new InputNameMenu(*this->window, this->font);

	this->imenu->addButton("SUBMIT", 500.f, "Submit");
	this->imenu->addButton("CANCEL", 600.f, "Cancel");
}

void GameState::initPlayer()
{
	this->player = new Player(0.f, 0.f, this->textures["PLAYER_RED_SHEET"]);
	this->player->setPosition(this->player->getSprite(), 3960.f, 336.f);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->font, this->player->getSprite());
}

void GameState::initNpc()
{
	this->nurse = new Npc(4340.f, 2265.f, this->textures["NPC_NURSE_SHEET"]);
	this->doctor = new Npc(522.f, 3516.f, this->textures["NPC_DOCTOR_SHEET"]);
	this->gymLeader = new Npc(3360.f, 3433.f, this->textures["NPC_GYM_LEADER_SHEET"]);
}

void GameState::initTeam()
{
	this->team = new Team(3);

	pokemons["Bulbasaur"] = new Pokemon(1, 10);
	pokemons["Charmander"] = new Pokemon(4, 10);
	pokemons["Squirtle"] = new Pokemon(7, 10);

	pokemons["Bulbasaur"]->getPokemonAttributeComponent()->buddy = true;

	this->team->add(pokemons["Bulbasaur"], 0);
	this->team->add(pokemons["Charmander"], 1);
	this->team->add(pokemons["Squirtle"], 2);

	pokemons["Pokemon1"] = new Pokemon(rand() % 100 + 1, 1);
}

void GameState::initTeamGUI()
{
	this->teamGUI = new TeamGUI(this->team, this->font);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 200, 200, "Resources/Images/Tiles/tilesheet.png");
	this->tileMap->loadFromFile("text.slmp");

	this->dialogBoxGUI = new DialogBoxGUI("Welcome to Pokemon KMITL.", this->font , *this->window);
}

// Constructors / Destructors

GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTexture();
	this->initPauseMenu();
	this->initInputNameMenu();

	this->initNpc();
	this->initPlayer();
	this->initPlayerGUI();
	this->initTeam();
	this->initTeamGUI();
	this->initTileMap();

	this->CreditScreen.setFillColor(sf::Color::Black);
	this->CreditScreen.setSize(sf::Vector2f(this->window->getSize()));

	this->CreditText.setFont(this->font);
	this->CreditText.setCharacterSize(50);
	this->CreditText.setString("Credits\n\nScript Writer\n-Nithi Nomprawat-\n\nAnimation/Graphics\n-Pokemon MMO-\n\nMusic/SFX\n-Pokemon Gameboy-\n\nSpecial Thank\n-Suraj Sharma-\n\n\n*Nithi Nomprawat*\n*62010497*\n\n-////- Thank you. -////-");
	this->CreditText.setPosition(
		sf::Vector2f(
			this->window->getSize().x / 2 - this->CreditText.getGlobalBounds().width / 2,
			this->window->getSize().y
		)
	);
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->imenu;
	delete this->player;
	delete this->playerGUI;
	delete this->team;
	delete this->teamGUI;
	delete this->tileMap;

	this->stateData->setMusic("Resources/Audios/Music/mainmenustate.ogg");
}

// Functions

void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x),
		std::floor(this->player->getPosition().y)
	);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && this->getKeytime())
	{
		this->isCheatMode = !this->isCheatMode;

		if (this->isCheatMode)
		{
			this->player->setCoins(3000);

			for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
			{
				for (unsigned i = 1; i <= 50; i++)
					it->second->getPokemonAttributeComponent()->gainExp(it->second->getPokemonAttributeComponent()->expNext);
			}

			this->player->playHeal();
		}
		else
		{
			this->player->setCoins(-3000);

			for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
			{
				if (it->second->getPokemonAttributeComponent()->level - 50 > 30)
				{
					it->second->getPokemonAttributeComponent()->attributePoints -= 50;
				}
				else
				{
					if (it->second->getPokemonAttributeComponent()->level - 50 < 30)
					{
						it->second->getPokemonAttributeComponent()->id -= 1;
						it->second->getPokemonAttributeComponent()->attributePoints -= it->second->getPokemonAttributeComponent()->level - 30;
						it->second->getPokemonAttributeComponent()->attributePoints -= it->second->getPokemonAttributeComponent()->attributePoints / 3;
						it->second->getPokemonAttributeComponent()->attributePoints -= 10;

						if (it->second->getPokemonAttributeComponent()->level - 50 < 20)
						{
							it->second->getPokemonAttributeComponent()->id -= 1;
							it->second->getPokemonAttributeComponent()->attributePoints -= it->second->getPokemonAttributeComponent()->attributePoints / 3;
						}
						it->second->getPokemonAttributeComponent()->attributePoints -= 70 - it->second->getPokemonAttributeComponent()->level;
					}
				}

				it->second->getPokemonAttributeComponent()->level -= 50;
				it->second->getPokemonAttributeComponent()->expNext = static_cast<int>((50 / 3) * (pow(it->second->getPokemonAttributeComponent()->level + 1, 3) - 7 * pow(it->second->getPokemonAttributeComponent()->level + 1, 2) + ((it->second->getPokemonAttributeComponent()->level + 1) * 17) - 12));
				it->second->getPokemonAttributeComponent()->updateStats(true);
			}
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	// Update player input

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && this->getKeytime())
	{
		if (this->player->getCoins() >= 90)
		{
			this->player->setCoins(-90);

			for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
			{
				it->second->getPokemonAttributeComponent()->gainHP(it->second->getPokemonAttributeComponent()->hpMax);
			}

			this->player->playHeal();
		}
	}
}

void GameState::updateTeamBuddy(const float& dt)
{

	for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
	{
		if (it->second->getPokemonAttributeComponent()->buddy)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("BUDDY_UP"))) && this->getKeytime())
			{
				if (it != this->pokemons.begin())
				{
					it->second->getPokemonAttributeComponent()->buddy = false;
					std::advance(it, -1);
					it->second->getPokemonAttributeComponent()->buddy = true;
					std::advance(it, 1);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("BUDDY_DOWN"))) && this->getKeytime())
			{
				std::advance(it, 1);
				if (it != this->pokemons.end())
				{
					it->second->getPokemonAttributeComponent()->buddy = true;
					std::advance(it, -1);
					it->second->getPokemonAttributeComponent()->buddy = false;
				}
				else
					std::advance(it, -1);
			}
		}

		sf::Vector2f direction = this->player->getPosition() - it->second->getPosition();

		if (abs(direction.x) > 224 || abs(direction.y) > 128)
			it->second->setPosition(it->second->getSprite(), this->player->getPosition().x - 28.f, this->player->getPosition().y - 16.f);

		if (floor(direction.y) < 16)
			it->second->move(0.f, -1.f, dt);
		if (floor(direction.y) > 16)
			it->second->move(0.f, 1.f, dt);
		if (floor(direction.x) < 28)
			it->second->move(-1.f, 0.f, dt);
		if (floor(direction.x) > 28)
			it->second->move(1.f, 0.f, dt);

		if (floor(direction.x) == 28 && floor(direction.y) == 16)
			it->second->stopVelocity();
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateBattleMenuButtons()
{
	this->bmenu->update(this->mousePosWindow);

	for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
	{
		if (it->second->getPokemonAttributeComponent()->buddy && it->second->getPokemonAttributeComponent()->hp != 0)
		{
			if (this->bmenu->isButtonPressed("FIGHT"))
			{
				if (!this->bmenu->isFightMenu() && !this->bmenu->getEnd())
					sf::sleep(sf::seconds(0.2f));
				this->bmenu->setFightMenu(true);
			}
		}
	}

	if (this->bmenu->isButtonPressed("POKEMON") && !this->bmenu->isSelectPokemon())
	{
		this->bmenu->setSelectPokemon(true);
		sf::sleep(sf::seconds(0.2f));
	}

	if (this->bmenu->isFightMenu())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
			this->bmenu->setFightMenu(false);

		for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
		{
			if (it->second->getPokemonAttributeComponent()->buddy)
			{
				if (this->bmenu->isButtonPressed("SKILL1") && this->getKeytime())
				{
					this->bmenu->attack(it->second->getPokemonAttributeComponent()->attack + rand() % 11 - 5);
					it->second->playSound("ATTACK");
					this->bmenu->enemySkill();
				}
				else if (this->bmenu->isButtonPressed("SKILL2") && this->getKeytime())
				{
					this->bmenu->attack((rand() % 3 == 2) ? it->second->getPokemonAttributeComponent()->attack * 1.5 : it->second->getPokemonAttributeComponent()->attack / 1.5);
					it->second->playSound("COUNTER");
					this->bmenu->enemySkill();
				}
				else if (this->bmenu->isButtonPressed("SKILL3") && it->second->getPokemonAttributeComponent()->level >= 15 && !this->healUsed && this->getKeytime())
				{
					this->healUsed = true;

					it->second->getPokemonAttributeComponent()->gainHP(it->second->getPokemonAttributeComponent()->hpMax);
					it->second->playSound("HEAL");
					this->bmenu->enemySkill();
				}
				else if (this->bmenu->isButtonPressed("SKILL4") && it->second->getPokemonAttributeComponent()->level >= 20 && !this->ultimateUsed && this->getKeytime())
				{
					this->ultimateUsed = true;

					srand(time(NULL));

					this->bmenu->attack((rand() % 5 == 4) ? it->second->getPokemonAttributeComponent()->attack * 5 : it->second->getPokemonAttributeComponent()->attack * 2);
					it->second->playSound("ULTIMATE");
					this->bmenu->enemySkill();
				}
			}
		}
	}

	if (this->bmenu->isSelectPokemon())
	{
		if (this->bmenu->isButtonPressed("POKEMON1") && this->getKeytime() && this->team->pokemonArray[0]->getPokemonAttributeComponent()->hp != 0 && !this->team->pokemonArray[0]->getPokemonAttributeComponent()->buddy)
		{
			this->bmenu->setPokemon(0);
			this->bmenu->enemySkill();
			this->bmenu->setSelectPokemon(false);
			sf::sleep(sf::seconds(0.2f));
		}
		else if (this->bmenu->isButtonPressed("POKEMON2") && this->getKeytime() && this->team->pokemonArray[1]->getPokemonAttributeComponent()->hp != 0 && !this->team->pokemonArray[1]->getPokemonAttributeComponent()->buddy)
		{
			this->bmenu->setPokemon(1);
			this->bmenu->enemySkill();
			this->bmenu->setSelectPokemon(false);
			sf::sleep(sf::seconds(0.2f));
		}
		else if (this->bmenu->isButtonPressed("POKEMON3") && this->getKeytime() && this->team->pokemonArray[2]->getPokemonAttributeComponent()->hp != 0 && !this->team->pokemonArray[2]->getPokemonAttributeComponent()->buddy)
		{
			this->bmenu->setPokemon(2);
			this->bmenu->enemySkill();
			this->bmenu->setSelectPokemon(false);
			sf::sleep(sf::seconds(0.2f));
		}
		else if (this->bmenu->isButtonPressed("BACK") && this->getKeytime())
		{
			this->bmenu->setSelectPokemon(false);
			sf::sleep(sf::seconds(0.2f));
		}
	}

	if (this->bmenu->isButtonPressed("RUN") || this->bmenu->isButtonPressed("EXIT"))
	{
		if (this->bmenu->enemyPokemon->getPokemonAttributeComponent()->hp == 0)
		{
			if (this->gymBattle)
			{
				this->gymCount++;
			}

			this->player->setCoins(50);

			if (this->questProgress < 100)
			{
				std::stringstream ss;

				switch (this->quest)
				{
				case 1:
					this->questProgress += 20;
					ss << "Quest Progress!.\n" << this->questProgress << " %";
					this->dialogBoxGUI = new DialogBoxGUI(ss.str(), this->font, *this->window);
					break;
				case 2:
					this->questProgress += 10;
					ss << "Quest Progress!.\n" << this->questProgress << " %";
					this->dialogBoxGUI = new DialogBoxGUI(ss.str(), this->font, *this->window);
					break;
				case 3:
					this->questProgress += 50;
					ss << "Quest Progress!.\n" << this->questProgress << " %";
					this->dialogBoxGUI = new DialogBoxGUI(ss.str(), this->font, *this->window);
					break;
				case 4:
					this->questProgress += 25;
					ss << "Quest Progress!.\n" << this->questProgress << " %";
					this->dialogBoxGUI = new DialogBoxGUI(ss.str(), this->font, *this->window);
					break;
				case 5:
					this->questProgress += 5;
					ss << "Quest Progress!,.\n" << this->questProgress << " %";
					this->dialogBoxGUI = new DialogBoxGUI(ss.str(), this->font, *this->window);
					break;
				case 6:
					this->questProgress += 20;
					ss << "Quest Progress!.\n" << this->questProgress << " %";
					this->dialogBoxGUI = new DialogBoxGUI(ss.str(), this->font, *this->window);
					break;
				case 7:
					this->questProgress += 10;
					ss << "Quest Progress!.\n" << this->questProgress << " %";
					this->dialogBoxGUI = new DialogBoxGUI(ss.str(), this->font, *this->window);
					break;
				}
			}
		}
		else if (this->gymBattle)
		{
			this->gymCount = 0;
			this->gymBattle = false;
			this->playerLose = true;
		}

		this->isBattle = !this->isBattle;
		this->healUsed = false;
		this->ultimateUsed = false;
		delete this->bmenu;

		this->stateData->setMusic("Resources/Audios/Music/gamestate.ogg");
	}
}

void GameState::updateInputNameMenuButtons()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
		this->endState();

	if (this->imenu->isButtonPressed("SUBMIT") || (this->isInputName && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(58))))
	{
		if (this->trainerName.size() == 0)
			this->trainerName = "Satoshi";
		this->isInputName = false;
	}
	if (this->imenu->isButtonPressed("CANCEL"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player, dt);
	if (this->tileMap->checkHopital(this->player, dt))
	{
		for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
		{
			it->second->getPokemonAttributeComponent()->gainHP(it->second->getPokemonAttributeComponent()->hpMax);

			if (this->quest == 9 && this->questProgress == 0)
			{
				this->questProgress += 100;
				this->dialogBoxGUI = new DialogBoxGUI("Quest Progress!.\n100 %", this->font, *this->window);
			}
		}

		this->playerLose = false;

		this->player->playHeal();
	}
	if (this->tileMap->checkQuest(this->player, dt) && !this->isQuest)
	{
		this->isQuest = true;
		this->isRewarded = false;
		this->quest = rand() % 10 + 1;
		this->questProgress = 0;

		switch (this->quest)
		{
		case 1:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 5 wild Pokemon.", this->font, *this->window);
			break;
		case 2:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 10 wild Pokemon.", this->font, *this->window);
			break;
		case 3:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 2 wild Pokemon.", this->font, *this->window);
			break;
		case 4:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 4 wild Pokemon.", this->font, *this->window);
			break;
		case 5:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 20 wild Pokemon.", this->font, *this->window);
			break;
		case 6:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 5 wild Pokemon.", this->font, *this->window);
			break;
		case 7:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 10 wild Pokemon.", this->font, *this->window);
			break;
		case 8:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nPick fruit from the house in the middle of the city.", this->font, *this->window);
			break;
		case 9:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nPlease take my Pokemon to the hospital.", this->font, *this->window);
			break;
		case 10:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nFeed the fish in the middle of the bridge.", this->font, *this->window);
			break;
		}
	}
	if (this->tileMap->checkQuest(this->player, dt) && this->questProgress == 100)
	{
		switch (this->quest)
		{
		case 1:
			this->player->setCoins(50 * 5);
			break;
		case 2:
			this->player->setCoins(50 * 10);
			break;
		case 3:
			this->player->setCoins(50 * 2);
			break;
		case 4:
			this->player->setCoins(50 * 4);
			break;
		case 5:
			this->player->setCoins(50 * 20);
			break;
		case 6:
			this->player->setCoins(50 * 5);
			break;
		case 7:
			this->player->setCoins(50 * 10);
			break;
		case 8:
			this->player->setCoins(50 * 3);
			break;
		case 9:
			this->player->setCoins(50 * 4);
			break;
		case 10:
			this->player->setCoins(50 * 5);
			break;
		}

		for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
		{
			it->second->getPokemonAttributeComponent()->gainExp(it->second->getPokemonAttributeComponent()->expNext);
		}

		this->isQuest = true;
		this->isRewarded = false;
		this->quest = rand() % 10 + 1;
		this->questProgress = 0;

		switch (this->quest)
		{
		case 1:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 5 wild Pokemon.", this->font, *this->window);
			break;
		case 2:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 10 wild Pokemon.", this->font, *this->window);
			break;
		case 3:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 2 wild Pokemon.", this->font, *this->window);
			break;
		case 4:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 4 wild Pokemon.", this->font, *this->window);
			break;
		case 5:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 20 wild Pokemon.", this->font, *this->window);
			break;
		case 6:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 5 wild Pokemon.", this->font, *this->window);
			break;
		case 7:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nDefeat the 10 wild Pokemon.", this->font, *this->window);
			break;
		case 8:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nPick fruit from the house in the middle of the city.", this->font, *this->window);
			break;
		case 9:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nPlease take my Pokemon to the hospital.", this->font, *this->window);
			break;
		case 10:
			this->dialogBoxGUI = new DialogBoxGUI("Quest Message!.\nFeed the fish in the middle of the bridge.", this->font, *this->window);
			break;
		}
	}
	this->tileMap->checkWarp(this->player, dt);
	if (this->tileMap->checkWildPokemon(this->player, dt) && !this->isBattle)
	{
		this->isBattle = true;
		this->bmenu = new BattleMenu(this->team, this->font, *this->window);

		this->healUsed = false;
		this->ultimateUsed = false;

		this->stateData->setMusic("Resources/Audios/Music/battlemenu.ogg");
	}
	for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
	{
		this->tileMap->updateCollision(it->second, dt);
	}
	if (this->quest == 8 && this->questProgress == 0)
	{
		if ((this->player->getPosition().x >= 888 && this->player->getPosition().x <= 1031) && (this->player->getPosition().y >= 1680 && this->player->getPosition().y <= 1799))
		{
			this->questProgress += 100;
			this->dialogBoxGUI = new DialogBoxGUI("Quest Progress!.\n100 %", this->font, *this->window);
		}
	}
	else if (this->quest == 10 && this->questProgress == 0)
	{
		if ((this->player->getPosition().x >= 1824 && this->player->getPosition().x <= 1895) && (this->player->getPosition().y >= 1080 && this->player->getPosition().y <= 1127))
		{
			this->questProgress += 100;
			this->dialogBoxGUI = new DialogBoxGUI("Quest Progress!.\n100 %", this->font, *this->window);
		}
	}
	if (this->tileMap->checkComeGym(this->player, dt) && this->player->getCoins() >= 3000)
	{
		this->player->setPosition(this->player->getSprite(), 3360.f, 3528.f);

		this->dialogBoxGUI = new DialogBoxGUI("Hit the gym leader to begin pokemon battle.", this->font, *this->window);
	}
	if (this->tileMap->checkLeaveGym(this->player, dt))
	{
		this->player->setPosition(this->player->getSprite(), 1104.f, 2160.f);
	}

	if (this->gymLeader->getGlobalBounds().intersects(this->player->getGlobalBounds()) && !this->playerLose && this->gymCount < 3)
	{
		this->gymBattle = true;

		this->isBattle = true;
		this->bmenu = new BattleMenu(this->team, this->font, *this->window, this->gymBattle);

		this->healUsed = false;
		this->ultimateUsed = false;

		this->stateData->setMusic("Resources/Audios/Music/battlemenu.ogg");
	}
}

void GameState::updateDialog()
{
	if ((this->player->getGlobalBounds().left >= 912 && this->player->getGlobalBounds().left <= 920) && (this->player->getGlobalBounds().top >= 48 && this->player->getGlobalBounds().top <= 311))
	{
		this->dialogBoxGUI = new DialogBoxGUI("In the grass there are wild Pokemon.\nYou can go into battle with it..", this->font, *this->window);
	}

	if ((this->player->getGlobalBounds().left >= 1704 && this->player->getGlobalBounds().left <= 1712) && (this->player->getGlobalBounds().top >= 48 && this->player->getGlobalBounds().top <= 311))
	{
		this->dialogBoxGUI = new DialogBoxGUI("Walk across the bridge to the KMITL village.\nthat is currently being built and developed.", this->font, *this->window);
	}

	if ((this->player->getGlobalBounds().left >= 1728 && this->player->getGlobalBounds().left <= 1991) && (this->player->getGlobalBounds().top >= 1368 && this->player->getGlobalBounds().top <= 1376))
	{
		this->dialogBoxGUI = new DialogBoxGUI("Welcome to KMITL village.", this->font, *this->window);
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);

	if (!this->isInputName)
	{
		if (!this->paused) // Unpaused update
		{
			if (!this->isBattle)
			{
				this->updateInput(dt);
				this->updateView(dt);

				if (!this->isBattle)
					this->updatePlayerInput(dt);

				this->updateTeamBuddy(dt);

				this->updateTileMap(dt);

				for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
				{
					it->second->update(dt);
				}

				this->player->update(dt);

				this->playerGUI->update(this->trainerName, dt);

				this->updateDialog();

				if (this->dialogBoxGUI != NULL)
				{
					this->dialogBoxGUI->update();

					if (this->dialogBoxGUI->index > this->dialogBoxGUI->message.length())
					{
						if (this->dialogBoxGUI->myClock.getElapsedTime() >= sf::seconds(1))
						{
							delete this->dialogBoxGUI;
							this->dialogBoxGUI = NULL;
						}
					}
				}
			}
			else
			{
				if (!this->bmenu->isFightMenu())
					this->updateInput(dt);

				this->updateBattleMenuButtons();
			}
		}
		else // Paused update
		{
			this->updateInput(dt);
			this->pmenu->update(this->mousePosWindow);
			this->updatePauseMenuButtons();
		}
	}
	else
	{
		this->imenu->update(this->mousePosWindow, this->trainerName);
		this->updateInputNameMenuButtons();
		if (this->stateData->events->type == sf::Event::TextEntered && this->getKeytime())
		{
			if (this->stateData->events->text.unicode == 8)
				this->trainerName = this->trainerName.substr(0, this->trainerName.size() - 1);
			else if (this->trainerName.length() < 8)
				this->trainerName += this->stateData->events->text.unicode;
		}
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)));

	for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
	{
		if (it->second->getPokemonAttributeComponent()->buddy)
		{
			it->second->render(this->renderTexture);
		}
	}

	this->nurse->render(this->renderTexture);
	this->doctor->render(this->renderTexture);
	this->gymLeader->render(this->renderTexture);

	this->player->render(this->renderTexture);

	this->tileMap->renderDeferred(this->renderTexture);

	std::stringstream ss;
	ss << "Press \"W\" to WALK UP.\n"
		<< "Press \"A\" to WALK LEFT.\n"
		<< "Press \"S\" to WALK DOWN.\n"
		<< "Press \"D\" to WALK RIGHT.";

	sf::Text tutorial, tutorialHeal;
	tutorial.setFont(this->font);
	tutorial.setString(ss.str());
	tutorial.setPosition(3700.f, 466.f);

	ss.str("");
	ss << "Press \"H\" to HEAL ALL POKEMON (use money).";

	tutorialHeal.setFont(this->font);
	tutorialHeal.setString(ss.str());
	tutorialHeal.setPosition(3500.f, 636.f);

	this->renderTexture.draw(tutorial);
	this->renderTexture.draw(tutorialHeal);

	// Render GUI

	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);
	this->teamGUI->render(this->renderTexture);

	if (this->dialogBoxGUI != NULL)
		this->dialogBoxGUI->render(this->renderTexture);

	if (this->isBattle)
		this->bmenu->render(this->renderTexture);

	if (this->isInputName) // Input name menu render
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->imenu->render(this->renderTexture);
	}

	if(this->paused) // Pause menu render
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	if (this->isCheatMode)
	{
		sf::Text text;
		text.setFont(this->font);
		text.setFillColor(sf::Color::Red);
		text.setString("Debug Mode is On");
		text.setPosition(this->renderTexture.getSize().x - text.getGlobalBounds().width - 10, 0);

		this->renderTexture.draw(text);
	}

	if (this->gymCount == 3)
	{
		this->renderTexture.draw(this->CreditScreen);
		this->renderTexture.draw(this->CreditText);
		this->CreditText.move(0, -0.3);

		if (this->CreditText.getGlobalBounds().top <= -this->CreditText.getGlobalBounds().height)
		{
			std::string key;
			unsigned num;

			std::map<std::string, unsigned> scores;

			std::ifstream in_file("text.score");


			while (in_file >> key >> num)
				scores[key] = num;

			std::ofstream out_file("text.score");

			for (auto& i : scores)
			{
				out_file << i.first << " " << i.second << "\n";
			}

			num = 0;

			if (this->myClock.getElapsedTime() < sf::seconds(1200))
				num += (1200 - this->myClock.getElapsedTime().asSeconds()) * 10;

			for (auto it = this->pokemons.begin(); it != this->pokemons.end(); ++it)
				num += it->second->getPokemonAttributeComponent()->level * 10;

			num += this->player->getCoins() * 10;

			out_file << this->trainerName << " " << num << "\n";

			this->endState();
		}
	}

	// Final render

	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}