#ifndef OOPPROJECT_AnimatedGif_H
#define OOPPROJECT_AnimatedGif_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <tuple>

class AnimatedGif
{
public:
    AnimatedGif(const char* filename);

    const sf::Vector2i& getSize(void);
    void update(sf::Sprite& sprite);

private:
    sf::Vector2i size;
    sf::Clock clock;
    sf::Time startTime;
    sf::Time totalDelay;
    std::vector<std::tuple<int, sf::Texture>> frames;
    std::vector<std::tuple<int, sf::Texture>>::iterator frameIter;
};

#endif //OOPPROJECT_AnimatedGif_H
