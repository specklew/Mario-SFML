#include "Resources/ResourceRegistry.h"

ResourceRegistry* ResourceRegistry::instance{nullptr};
std::mutex ResourceRegistry::mutex;

ResourceRegistry::ResourceRegistry() {
    initObjects();
}

ResourceRegistry::~ResourceRegistry(){
    for(auto object : resourceMap){
        delete object.second;
    }
}

ResourceRegistry * ResourceRegistry::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new ResourceRegistry();
    }
    return instance;
}

void ResourceRegistry::initObjects() {

    sf::IntRect basicRect(0, 0, (int)tileSize, (int)tileSize);

    auto* airTile = new Resource(TILE, relativeTexturePath + "Air.png", basicRect);
    auto* groundTile = new Resource(TILE, relativeTexturePath + "Ground.png", basicRect);
    auto* brickTile = new Resource(TILE, relativeTexturePath + "BrickBlockBrown.png", basicRect);
    auto* blockTile = new Resource(TILE, relativeTexturePath + "Block.png", basicRect);
    auto* coinTile = new Resource(ENTITY, relativeTexturePath + "CoinForBlueBG.gif", basicRect);
    auto* goombaEntity = new Resource(ENTITY, relativeTexturePath + "LittleGoomba.gif", basicRect);
    auto* pplantEntity = new Resource(ENTITY, relativeTexturePath + "PiranhaPlant.gif", basicRect);


    resourceMap.insert({AIR_TILE_ID, airTile});
    resourceMap.insert({GROUND_TILE_ID, groundTile});
    resourceMap.insert({BRICK_TILE_ID, brickTile});
    resourceMap.insert({BLOCK_TILE_ID, blockTile});
    resourceMap.insert({COIN_ENTITY_ID, coinTile});
    resourceMap.insert({GOOMBA_ENTITY_ID, goombaEntity});
    resourceMap.insert({PPLANT_ENTITY_ID, pplantEntity});

}

unsigned int ResourceRegistry::getTileSize() const {
    return tileSize;
}

Resource * ResourceRegistry::getPresetById(unsigned int id) {
    return resourceMap.at(id);
}
