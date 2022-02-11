#ifndef OOPPROJECT_RESOURCE_H
#define OOPPROJECT_RESOURCE_H

#include <SFML/Graphics.hpp>
#include "AnimatedGif.h"

enum ResourceType{
    TILE,
    ENTITY
};

class Resource{

    ResourceType type;

    sf::IntRect rect;

    sf::Texture texture;
    AnimatedGif gif;

public:

    Resource(ResourceType type, std::string textureAddress, sf::IntRect rect);

    ResourceType getType() const {return type;}

    sf::IntRect getRect() {return rect;}

    const sf::Texture &getTexture() const {return texture;}

    AnimatedGif &getGif() {return gif;}
};

#endif //OOPPROJECT_RESOURCE_H
