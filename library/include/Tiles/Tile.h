#ifndef OOPPROJECT_TILE_H
#define OOPPROJECT_TILE_H

#include <SFML/Graphics.hpp>
#include "Resources/ResourceRegistry.h"
#include "Resources/Resource.h"

class Tile{

    Resource * type;
    sf::Sprite sprite;

public:

    Tile() = default;
    explicit Tile(Resource * type);
    ~Tile();

    void setTilePosition(int x, int y);
    void render(sf::RenderTarget & renderTarget);

    sf::FloatRect getGlobalBounds();
    Resource * getTilePreset();
};

#endif //OOPPROJECT_TILE_H
