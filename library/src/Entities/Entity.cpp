#include "Entities/Entity.h"

Entity::Entity(Resource *base, int damage, float acceleration, CollisionStrategy *strategy) {
    this->base = base;
    this->damage = damage;
    this->acceleration = acceleration;
    this->strategy = strategy;

    this->sprite.setTexture(Entity::getBase()->getTexture());
    this->sprite.setOrigin(this->sprite.getTextureRect().width / 2, this->sprite.getTextureRect().height);
}

Entity::~Entity() {
    delete this->strategy;
}

void Entity::render(sf::RenderTarget &target){
    target.draw(this->sprite);
}


void Entity::update() {
    this->updatePhysics();
    this->updateMovement();
    this->base->getGif().update(this->sprite);

}

void Entity::updatePhysics() {
    velocity.y += gravity/1000;
}

void Entity::checkCollisions(Tile **allTiles, int levelHeight, int levelLength) {

    //Get the tile preset that is not solid:
    ResourceRegistry * tileRegistry = ResourceRegistry::GetInstance();
    Resource * airPreset = tileRegistry->getPresetById(0);

    for (int i = 0; i < levelHeight; ++i) {
        for (int j = 0; j < levelLength; ++j) {
            sf::FloatRect tileBounds = allTiles[i][j].getGlobalBounds();
            //Check if player intersects with any tile in the level

            if(tileBounds.intersects(this->sprite.getGlobalBounds()) && allTiles[i][j].getTilePreset() != airPreset){

                float tileLeft = tileBounds.left;
                float tileRight = tileBounds.left + tileBounds.width;
                float tileTop = tileBounds.top;
                float tileBottom = tileBounds.top + tileBounds.height;
                sf::Vector2f tilePos(tileLeft + tileBounds.width / 2, tileTop + tileBounds.height / 2);

                float playerLeft = this->sprite.getGlobalBounds().left;
                float playerRight = this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width;
                float playerTop = this->sprite.getGlobalBounds().top;
                float playerBottom = this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height;

                sf::Vector2f delta = tilePos - this->sprite.getPosition();

                float intersectX = 0.0f, intersectY = 0.0f;

                if(delta.y > 0)
                {
                    if(delta.x > 0)
                    {
                        intersectX = playerRight - tileLeft;
                        intersectY = playerBottom - tileTop;
                    }
                    else
                    {
                        intersectX = playerLeft - tileRight;
                        intersectY = playerBottom - tileTop;
                    }
                }
                else
                {
                    if(delta.x > 0)
                    {
                        intersectX = playerRight - tileLeft;
                        intersectY = playerTop - tileBottom;
                    }
                    else
                    {
                        intersectX = playerLeft - tileRight;
                        intersectY = playerTop - tileBottom;
                    }
                }

                if(std::abs(intersectX) < std::abs(intersectY)){
                    setPositionX(this->sprite.getPosition().x - intersectX);
                }
                else{
                    setPositionY(this->sprite.getPosition().y - intersectY - 0.1f);
                    velocity.y -= velocity.y;
                }
            }
        }
    }
}

//Private setters:

void Entity::setPositionX(float x) {
    this->sprite.setPosition(x, this->sprite.getPosition().y);
}
void Entity::performCollisionStrategy(int data) {

    this->strategy->performCollisionStrategy(data);
}

void Entity::setPositionY(float y) {
    this->sprite.setPosition(this->sprite.getPosition().x, y);
}

//Public setters:

void Entity::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Entity::setPosition(sf::Vector2f position) {
    this->sprite.setPosition(position);
}

void Entity::setTilePosition(int x, int y) {
    ResourceRegistry * resourceRegistry = ResourceRegistry::GetInstance();
    this->sprite.setPosition((float)x * (float)resourceRegistry->getTileSize(), (float)y * (float)resourceRegistry->getTileSize());
}