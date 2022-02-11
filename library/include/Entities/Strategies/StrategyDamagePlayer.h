#ifndef OOPPROJECT_STRATEGYDAMAGEPLAYER_H
#define OOPPROJECT_STRATEGYDAMAGEPLAYER_H

#include "CollisionStrategy.h"

class StrategyDamagePlayer : public CollisionStrategy{
public:
    void performCollisionStrategy(int data) const override;
};

#endif //OOPPROJECT_STRATEGYDAMAGEPLAYER_H
