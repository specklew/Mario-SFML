#include "Level.h"


Level::Level(const std::string& fileName) {

    ResourceRegistry * resourceRegistry = ResourceRegistry::GetInstance();
    entityFactory = std::make_unique<EntityFactory>();

    std::fstream levelFile;
    levelFile.open( "../../levels/" + fileName, std::ios::in);

    if(levelFile.is_open()){

        int i = 0;
        std::string str;
        while(std::getline(levelFile, str)){
            if(i == 0){
                int j = 0;
                bool done = false;
                std::string x;
                for(char& c : str) {
                    j++;
                    if(c == ';' && !done){
                        length = stoi(x);
                        done = true;
                        x = "";
                        continue;
                    }
                    if(c == ';'){
                        height = stoi(x);
                        initArray();
                        continue;
                    }
                    x += c;
                }
                initBackgroundTexture();

                i++;
                continue;
            }

            //Start assigning tiles.
            int j = 0;
            for(char c : str) {

                int num = c - 48;

                if(resourceRegistry->getPresetById(num)->getType() == TILE) {
                    Tile *newTile = new Tile(resourceRegistry->getPresetById(num));
                    tiles[i - 1][j] = *newTile;
                }else if(resourceRegistry->getPresetById(num)->getType() == ENTITY){
                    Tile *newTile = new Tile(resourceRegistry->getPresetById(0));
                    tiles[i - 1][j] = *newTile;

                    Entity * entity = entityFactory->CreateEntity(num);


                    entity->setTilePosition(j, i);

                    entities.push_back(entity);
                }

                j++;
            }

            i++;
        }
    }
    else
    {
        throw std::runtime_error("The level could not be found! Level file passed: " + fileName);
    }
    initTilePositions();
}

void Level::initBackgroundTexture() {

    ResourceRegistry * resourceRegistry = ResourceRegistry::GetInstance();

    backgroundTexture.loadFromFile(resourceRegistry->relativeTexturePath + "background.png");
    auto backgroundSprite = std::make_shared<sf::Sprite>(backgroundTexture);
    backgroundSprite->setPosition(0.0F,0.f);
    backgroundSprite->setScale(0.22f,0.22f);

    backgrounds.push_back(backgroundSprite);
    for(int i = 1; (float)i * backgroundSprite->getGlobalBounds().width < (float)this->getLevelLength() * (float)resourceRegistry->tileSize; ++i){
        auto newSprite = std::make_shared<sf::Sprite>(backgroundTexture);
        newSprite->setPosition((float)i * backgroundSprite->getGlobalBounds().width, 0.0f);
        newSprite->setScale(0.22f, 0.22f);
        backgrounds.push_back(newSprite);
    }
}

void Level::initArray() {
    tiles = new Tile* [height];

    for (int i=0; i < height; ++i)
    {
        tiles[i] = new Tile[length];
    }
}

void Level::initTilePositions() {
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < length; ++j){
            tiles[i][j].setTilePosition(j, i);
        }
    }
}

void Level::render(sf::RenderTarget & renderTarget) {

    for(const auto& background : backgrounds){
        renderTarget.draw(*background);
    }

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < length; ++j){
            tiles[i][j].render(renderTarget);
        }
    }

    for(auto entity : entities){
        entity->render(renderTarget);
    }
}

void Level::update() {
    for(auto entity : entities){
        entity->update();
        entity->checkCollisions(this->tiles, this->height, this->length);
    }
}

Level::~Level() {
    for(int i=0; i < height; i++)    //To delete the inner arrays
        delete [] tiles[i];
    delete [] tiles;
    for(auto entity : entities) {
        delete entity;
    }
}