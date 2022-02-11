#ifndef OOPPROJECT_GOOMBA_H
#define OOPPROJECT_GOOMBA_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Entities/Strategies/StrategyDamagePlayer.h"
#include <ctime>

class Goomba : public Entity{
protected:
    int damage{1};
    float acceleration{6};

public:
    Goomba(Resource * base);
    ~Goomba();

    void updatePhysics() override ;
    void updateMovement() override;

    void move(float dir_x, float dir_y) override;

};

#endif //OOPPROJECT_GOOMBA_H
