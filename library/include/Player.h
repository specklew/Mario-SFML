#ifndef OOPPROJECT_PLAYER_H
#define OOPPROJECT_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Resources/ResourceRegistry.h"
#include "AnimatedGif.h"
#include "Level.h"
#include "Entities/Entity.h"

class Player{

    sf::Sprite sprite;

    sf::Texture standingTexture;
    sf::Texture jumpingTexture;
    AnimatedGif gif;

    sf::Vector2f spawnPointPos;

    bool goingRight{false};
    bool goingLeft{false};
    bool goingToJump{false};

    unsigned int playerHealth{5};

    bool onGround{false};
    unsigned int jumpCount{0};

    //Physics:
    sf::Vector2f velocity{0,0};
    float gravity{10.f};
    float acceleration{0.2f};
    float maxVelocity{3.0f};
    float friction{0.5f};

    //Private methods:

    void updatePhysics();
    void updateMovement();
    void updateAnimations();
    void updateFallDamage();

    void move(float dir_x);
    void jump();

    void setPositionX(float x);
    void setPositionY(float y);

    void changeToStandingTexture();
    void changeToJumpingTexture(bool moveDirection);
    void changeToGif(bool moveDirection);

    void setOnGround(bool onGround);

    void checkIfPlayerShouldDie();

    //Collisions:
    sf::Vector2f getCollisionIntersection(sf::FloatRect nextPos);
    void enemyCollisions();


public:

    Player(int x , int y);

    //Render works like update but is run before update:
    void render(sf::RenderTarget & target);

    //Catching events before update:
    void catchEvents(sf::Event event);

    //Update functions run every frame.
    void update(sf::RenderTarget & target);

    //Getters:
    sf::FloatRect getPlayerBounds() {return this->sprite.getGlobalBounds();};
    sf::Vector2f getPos() {return sprite.getPosition();};
    unsigned int getHP() const  {return playerHealth;};

    void setPlayerPosition(sf::Vector2f position);
    void setPlayerPosition(int x, int y);

    void receiveDamage(int dmg);
};
#endif //OOPPROJECT_PLAYER_H