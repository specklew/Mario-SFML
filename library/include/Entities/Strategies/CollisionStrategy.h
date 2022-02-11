#ifndef OOPPROJECT_COLLISIONSTRATEGY_H
#define OOPPROJECT_COLLISIONSTRATEGY_H

class CollisionStrategy{
public:
    virtual ~CollisionStrategy();
    virtual void performCollisionStrategy(int data) const = 0;
};

#endif //OOPPROJECT_COLLISIONSTRATEGY_H
