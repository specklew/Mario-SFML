#ifndef OOPPROJECT_LEVEL_H
#define OOPPROJECT_LEVEL_H

#include <memory>
#include <fstream>

#include "Resources/ResourceRegistry.h"
#include "Tiles/Tile.h"

#include "Entities/EntityFactory.h"
#include "Entities/Entity.h"

class Level{

    Tile ** tiles;

    std::unique_ptr<EntityFactory> entityFactory;

    std::vector<Entity *> entities;

    sf::Texture backgroundTexture;
    std::vector<std::shared_ptr<sf::Sprite>> backgrounds;

    int height{10};
    int length{10};

    //Private methods:
    void initBackgroundTexture();
    void initArray();
    void initTilePositions();

public:

    friend class Player;
    explicit Level(const std::string& fileName);
    ~Level();

    void render(sf::RenderTarget & renderTarget);

    Tile** getAllTiles(){return tiles;};
    int getLevelHeight() const {return height;};
    int getLevelLength() const {return length;};

    void update();
};

#endif //OOPPROJECT_LEVEL_H
