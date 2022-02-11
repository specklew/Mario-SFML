#ifndef OOPPROJECT_COIN_H
#define OOPPROJECT_COIN_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Entities/Strategies/StrategyChangeLevel.h"
#include <ctime>


class Coin : public Entity{

public:
    Coin(Resource * base);
    ~Coin();

    void updatePhysics() override;
    void updateMovement() override;
    void move(float dir_x, float dir_y) override;

};

#endif //OOPPROJECT_COIN_H
