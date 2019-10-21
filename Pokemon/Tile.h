#ifndef TILE_H
#define TILE_H

enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile
{
private:

protected:

	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	// Accessors

	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	const std::string getAsString() const;

	// Functions

	void update();
	void render(sf::RenderTarget& target);
};

#endif