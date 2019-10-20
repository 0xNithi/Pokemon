#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0;x < this->maxSize.x;x++)
	{
		for (size_t y = 0;y < this->maxSize.y;y++)
		{
			for (size_t z = 0;z < this->layers;z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->texture_file = texture_file;

	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0;x < this->maxSize.x;x++)
	{
		for (size_t y = 0;y < this->maxSize.y;y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t z = 0;z < this->layers;z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
		throw "ERROR::TILEMAP::FAILED_TO_LOAD_TILETEXTURESHEET::FILENAME: " + texture_file;
}

TileMap::~TileMap()
{
	this->clear();
}

// Accessors

const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

// Functions

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	// Take three indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it.

	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			// Ok to add tile.

			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);

			std::cout << "DEBUG: ADDED TILE!" << "\n";
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	// Take three indicies from the mouse position in the grid and remove a tile to that position if the internal tilemap array allows it.

	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			// Ok to remove tile.

			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
			std::cout << "DEBUG: REMOVED TILE!" << "\n";
		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	 /*Save the entire tilemap to a text-file.
	 Format:
	 Basic:
	 Size x y
	 gridSize
	 layers
	 texture file

	 All tiles:
	 gridPos x y layer
	 Texture rect x y
	 collision, type
	 */

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->texture_file << "\n";

		for (size_t x = 0;x < this->maxSize.x;x++)
		{
			for (size_t y = 0;y < this->maxSize.y;y++)
			{
				for (size_t z = 0;z < this->layers;z++)
				{
					if(this->map[x][y][z])
						out_file << x << " " << y << " " << z << " "
						<< this->map[x][y][z]->getAsString() << " "; // Make sure this last space is not saved!
				}
			}
		}
	}
	else
	{
		throw "ERROR::TILEMAP::FAILED_TO_SAVE_TO_FILE::FILENAME: " + file_name;
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		// Basics

		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		// Tiles

		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->texture_file = texture_file;

		this->clear();

		this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
		for (size_t x = 0;x < this->maxSize.x;x++)
		{
			for (size_t y = 0;y < this->maxSize.y;y++)
			{
				this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

				for (size_t z = 0;z < this->layers;z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			throw "ERROR::TILEMAP::FAILED_TO_LOAD_TILETEXTURESHEET::FILENAME: " + texture_file;

		// Load all tiles

		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(
				x, y, 
				this->gridSizeF, 
				this->tileSheet, 
				sf::IntRect(
					trX, trY, 
					this->gridSizeU, this->gridSizeU
				), 
				collision, type
			);
		}
	}
	else
	{
		throw "ERROR::TILEMAP::FAILED_TO_LOAD_TO_FILE::FILENAME: " + file_name;
	}

	in_file.close();
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != NULL)
					z->render(target);
			}
		}
	}
}