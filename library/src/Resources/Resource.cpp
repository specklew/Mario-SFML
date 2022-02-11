#include "Resources/Resource.h"

Resource::Resource(ResourceType type, std::string textureAddress, sf::IntRect rect) : gif(textureAddress.c_str()){
    this->type = type;
    this->rect = rect;

    if(!this->texture.loadFromFile(textureAddress)){
        throw std::runtime_error("Could not load texture at: " + textureAddress);
    }
}