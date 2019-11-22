#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initProfile(sf::Sprite& sprite, std::string name)
{
	if (!this->profileTexture.loadFromFile("Resources/Images/UI/player_profile.png"))
	{
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_PLAYER_PROFILE";
	}

	this->profileBackground.setSize(sf::Vector2f(300.f, 80.f));
	this->profileBackground.setPosition(15.f, 15.f);
	this->profileBackground.setTexture(&this->profileTexture);

	this->profileSprite = sprite;
	this->profileSprite.setTextureRect(sf::IntRect(0, 16, 32, 64));
	this->profileSprite.setPosition(40.f, 30.f);

	this->profileText.setFont(this->font);
	this->profileText.setCharacterSize(20);
	this->profileText.setPosition(110.f, 30.f);
	std::stringstream ss;
	ss << "Trainer\n   " << std::setfill(' ') << std::setw(8) << name;
	this->profileText.setString(ss.str());
}

void PlayerGUI::initCoins()
{
	if (!this->coinsTexture.loadFromFile("Resources/Images/UI/coins.png"))
	{
		throw "ERROR::GAMESTATE::FAILED_TO_LOAD_COINS";
	}

	float x = 330;
	float y = 15;

	this->coinsRect.setSize(sf::Vector2f(170.f, 40.f));
	this->coinsRect.setPosition(x, y);
	this->coinsRect.setTexture(&this->coinsTexture);

	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << std::setfill(' ') << std::setw(6) << this->player->getCoins();
	this->coinsText.setFont(this->font);
	this->coinsText.setFillColor(sf::Color::Black);
	this->coinsText.setCharacterSize(20);
	this->coinsText.setPosition(x + 45, y + 8);
	this->coinsText.setString(ss.str());
}

PlayerGUI::PlayerGUI(Player* player, sf::Font& font, sf::Sprite& sprite, std::string name)
{
	this->player = player;

	this->font = font;

	this->initProfile(sprite, name);
	this->initCoins();
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::update(std::string name, const float& dt)
{
	std::stringstream ss;
	ss << "Trainer\n   " << std::setfill(' ') << std::setw(8) << name;
	this->profileText.setString(ss.str());

	ss.str("");
	ss.imbue(std::locale(""));
	ss << std::setfill(' ') << std::setw(6) << this->player->getCoins();
	this->coinsText.setString(ss.str());
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	target.draw(this->profileBackground);
	target.draw(this->profileSprite);
	target.draw(this->profileText);

	target.draw(this->coinsRect);
	target.draw(this->coinsText);
}
