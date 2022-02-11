#include "Tiles/Tile.h"

Tile::Tile(Resource * type) {

    this->type = type;
    this->sprite.setTexture(type->getTexture());
    this->sprite.setTextureRect(type->getRect());
    this->sprite.setScale(1,1);

}

Tile::~Tile() = default;

void Tile::setTilePosition(int x, int y) {
    ResourceRegistry * tileRegistry = ResourceRegistry::GetInstance();
    this->sprite.setPosition((float)(x*tileRegistry->getTileSize()), (float)(y*tileRegistry->getTileSize()));
}

void Tile::render(sf::RenderTarget & renderTarget) {
    renderTarget.draw(this->sprite);
}

sf::FloatRect Tile::getGlobalBounds() {
    return this->sprite.getGlobalBounds();
}

Resource * Tile::getTilePreset() {
    return this->type;
}

