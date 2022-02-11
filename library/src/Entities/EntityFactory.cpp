#include "Entities/EntityFactory.h"

EntityFactory::EntityFactory(){
this->resourceRegistry = ResourceRegistry::GetInstance();
}

Entity *EntityFactory::CreateEntity(unsigned int id) {

    switch (id) {
        case GOOMBA_ENTITY_ID:
            return new Goomba(resourceRegistry->getPresetById(GOOMBA_ENTITY_ID));
        case PPLANT_ENTITY_ID:
            return new PPlant(resourceRegistry->getPresetById(PPLANT_ENTITY_ID));
        case COIN_ENTITY_ID:
            return new Coin(resourceRegistry->getPresetById(COIN_ENTITY_ID));
        default:
            throw std::runtime_error(
                    "Entity factory could not find the enemy assigned with this enemy id: " + std::to_string(id));
    }

}