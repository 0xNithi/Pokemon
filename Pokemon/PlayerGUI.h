#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"

class Player;

class PlayerGUI
{
private:

	Player* player;

	sf::Font font;

	sf::Text coinsText;
	sf::Texture coinsTexture;
	sf::RectangleShape coinsRect;

	sf::Text profileText;
	sf::Texture profileTexture;
	sf::RectangleShape profileBackground;

	sf::Sprite profileSprite;

	void initProfile(sf::Sprite& sprite, std::string name);
	void initCoins();

public:

	PlayerGUI(Player* player, sf::Font& font, sf::Sprite& sprite, std::string name = "Satoshi");
	virtual ~PlayerGUI();

	// Functions

	void update(std::string name, const float& dt);
	void render(sf::RenderTarget& target);
};

#endif