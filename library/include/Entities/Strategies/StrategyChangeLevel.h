#ifndef OOPPROJECT_STRATEGYCHANGELEVEL_H
#define OOPPROJECT_STRATEGYCHANGELEVEL_H

#include "CollisionStrategy.h"

class StrategyChangeLevel : public CollisionStrategy{
public:
    void performCollisionStrategy(int data) const override;
};

#endif //OOPPROJECT_STRATEGYCHANGELEVEL_H
