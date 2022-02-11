#ifndef OOPPROJECT_ENTITY_H
#define OOPPROJECT_ENTITY_H

#include <SFML/Graphics.hpp>

#include "Resources/ResourceRegistry.h"
#include "Resources/Resource.h"
#include "Tiles/Tile.h"
#include "Entities/Strategies/CollisionStrategy.h"

class Entity{

    Resource * base;
    CollisionStrategy * strategy;

    int damage;

    void setPositionX(float x);
    void setPositionY(float y);

protected:
    //Physics:
    sf::Vector2f velocity{0,0};
    float maxVelocity{2.0f};
    float acceleration{0.2f};
    float gravity{10.f};

    sf::Sprite sprite;

public:

    friend class Player;

    Entity(Resource *base, int damage, float acceleration, CollisionStrategy *strategy);
    virtual ~Entity();

    //Update functions run every frame.
    virtual void update();
    virtual void updatePhysics()=0;
    virtual void updateMovement()=0;

    void render(sf::RenderTarget & target);

    virtual void move(float dir_x, float dir_y)=0;

    void checkCollisions(Tile **tiles, int levelHeight, int levelLength);

    void setPosition(float x, float y);
    void setPosition(sf::Vector2f position);
    void setTilePosition(int x, int y);

    void performCollisionStrategy(int data);

    //Getters
    Resource * getBase(){ return base; };
};

#endif //OOPPROJECT_ENTITY_H
