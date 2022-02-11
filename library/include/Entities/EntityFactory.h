#ifndef OOPPROJECT_ENTITYFACTORY_H
#define OOPPROJECT_ENTITYFACTORY_H

#include "Resources/ResourceRegistry.h"
#include "Entities/Entity.h"
#include "Entities/Goomba.h"
#include "Entities/PPlant.h"
#include "Entities/Coin.h"

class EntityFactory{

    ResourceRegistry * resourceRegistry;

public:
    EntityFactory();
    ~EntityFactory()= default;

    Entity * CreateEntity(unsigned int id);
};

#endif //OOPPROJECT_ENTITYFACTORY_H
