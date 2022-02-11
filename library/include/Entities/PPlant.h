#ifndef OOPPROJECT_PPLANT_H
#define OOPPROJECT_PPLANT_H

#include "Entity.h"
#include "Strategies/StrategyDamagePlayer.h"

class PPlant : public Entity {
    int damage{2};
    float acceleration{0};

public:
    PPlant(Resource * base);
    ~PPlant();

    void updatePhysics() override;
    void updateMovement() override;

    void move(float dir_x, float dir_y) override;

};

#endif //OOPPROJECT_PPLANT_H
