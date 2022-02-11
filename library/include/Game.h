#ifndef OOPPROJECT_GAME_H
#define OOPPROJECT_GAME_H

#include <vector>
#include <mutex>
#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Player.h"
#include "Resources/ResourceRegistry.h"

class Game{

    //Static singleton variables:
    static Game * instance;
    static std::mutex mutex;

    //The rest of variables:

    bool running{true};
    int currentLevelId{0};

    sf::RenderWindow window;
    sf::VideoMode videoMode;
    sf::Event event;
    sf::View view {sf::Vector2f(0.0f,0.0f),sf::Vector2f(1000.0f,800.0f)};

    std::vector<Level*> levels;

    //Private methods:
    void initWindow();
    void initLevels();

    void pollEvents();

    void applyCorrectScreenCenter();

protected:
    //The constructor and destructor are protected to prevent calls with "new/delete".
    Game();
    ~Game();
public:

    Player * player;

    //Singleton functionality.
    //Deletes the possibility to clone the game class.
    Game(Game &other) = delete;
    void operator=(const Game &) = delete;

    static Game * GetInstance();

    //Game functions:
    void update();
    void render();

    //Getters:
    bool isRunning() const{return running;};
    Level * getCurrentLevel(){return levels.at(this->currentLevelId);};
    int getCurrentLevelId() const {return currentLevelId;};

    //Sort of setters:
    void changeLevel(int levelId);
};

#endif //OOPPROJECT_GAME_H
