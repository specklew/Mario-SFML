#include "Player.h"
#include "Game.h"

Player::Player(int x , int y) : gif("../../textures/Mario.gif"){

    spawnPointPos.x = (float)x;
    spawnPointPos.y = (float)y;

    //Loading textures:
    if(!this->standingTexture.loadFromFile("../../textures/MarioStanding.png")){
        throw std::runtime_error("Could not load texture mario standing texture.");
    }

    if(!this->jumpingTexture.loadFromFile("../../textures/MarioJumping.png")){
        throw std::runtime_error("Could not load texture mario jumping texture.");
    }

    //Setting textures:
    this->sprite.setTexture(this->standingTexture);
    this->sprite.setTextureRect({0, 0, (int)this->standingTexture.getSize().x, (int)this->standingTexture.getSize().y});

    //Setting position and origin of sprite:
    this->sprite.setPosition((float)x,(float)y);
    this->sprite.setOrigin((float)this->sprite.getTextureRect().width/2, (float)this->sprite.getTextureRect().height);
}

#pragma region Update_Functions

void Player::update(sf::RenderTarget & target){

    this->updatePhysics();
    this->updateMovement();

    this->updateAnimations();

    this->updateFallDamage();
}

void Player::updatePhysics() {

    this->enemyCollisions();

    velocity.y += gravity/100;

    sf::FloatRect nextPos = sprite.getGlobalBounds();

    nextPos.left += velocity.x;
    nextPos.top += velocity.y;

    //For now the collision algorithm is good enough... but it could use some refinement.
    velocity -= getCollisionIntersection(nextPos);

    velocity.x = std::round(velocity.x * 10000) / 10000;
    velocity.y = std::round(velocity.y * 10000) / 10000;

    if(std::abs(velocity.y) != 0) setOnGround(false);

    this->sprite.move(velocity);
}

void Player::updateMovement() {

    if(goingLeft)
    {
        this->move(-1);
    }
    else if(goingRight)
    {
        this->move(1);
    }
    else{
        this->velocity.x=0;
    }

    if(goingToJump && (onGround || jumpCount < 2)){
        this->jump();
            jumpCount += 1;
            goingToJump = false;
    }
}

void Player::updateAnimations() {
    if(std::abs(this->velocity.x) > 0.1f && onGround) {
        this->gif.update(this->sprite);
    }
}

void Player::updateFallDamage() {

    Game * game = Game::GetInstance();
    ResourceRegistry * resourceRegistry = ResourceRegistry::GetInstance();

    if(this->getPos().y > (float)(game->getCurrentLevel()->height * resourceRegistry->tileSize) + 16.0f){

        this->playerHealth = 0;
        checkIfPlayerShouldDie();
    }
}

void Player::catchEvents(sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Key::D:
                    goingRight = true;
                    if(onGround) changeToGif(true);
                    break;

                case sf::Keyboard::Key::A:
                    goingLeft = true;
                    if(onGround) changeToGif(false);
                    break;

                case sf::Keyboard::Key::W:
                case sf::Keyboard::Key::Space:
                    goingToJump = true;
                    break;
                default:

                    break;
            }
            break;

        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
                case sf::Keyboard::Key::D:
                    goingRight = false;
                    break;

                case sf::Keyboard::Key::A:
                    goingLeft = false;
                    break;

                default:

                    break;
            }
            break;

        default:

            break;
    }
}

void Player::render(sf::RenderTarget & target) {
    target.draw(this->sprite);
}

#pragma endregion

#pragma region Collision_Detection

sf::Vector2f Player::getCollisionIntersection(sf::FloatRect nextPos) {

    //Get all the tiles from the current level:
    Game * game = Game::GetInstance();
    Level * currentLevel = game->getCurrentLevel();
    Tile** allTiles = currentLevel->getAllTiles();


    //Get the tile preset that is not solid:
    ResourceRegistry * tileRegistry = ResourceRegistry::GetInstance();
    Resource * airPreset = tileRegistry->getPresetById(0);

    sf::Vector2f vectorSum{0,0};

    for (int i = 0; i < currentLevel->getLevelHeight(); ++i) {
        for (int j = 0; j < currentLevel->getLevelLength(); ++j) {
            if (allTiles[i][j].getTilePreset() == airPreset) continue;
            sf::FloatRect tileBounds = allTiles[i][j].getGlobalBounds();

            //Check if player intersects with any tile in the level

            if (tileBounds.intersects(nextPos)) {

                float tileLeft = tileBounds.left;
                float tileRight = tileBounds.left + tileBounds.width;
                float tileTop = tileBounds.top;
                float tileBottom = tileBounds.top + tileBounds.height;

                float playerLeft = nextPos.left;
                float playerRight = nextPos.left + nextPos.width;
                float playerTop = nextPos.top;
                float playerBottom = nextPos.top + nextPos.height;

                sf::Vector2f delta = {tileLeft - playerLeft, tileTop - playerTop};

                float intersectX = 0.0f, intersectY = 0.0f;

                if(delta.y > 0)
                {
                    if(delta.x > 0)
                    {
                        intersectX = playerRight - tileLeft;
                        intersectY = playerBottom - tileTop;
                    }
                    else
                    {
                        intersectX = playerLeft - tileRight;
                        intersectY = playerBottom - tileTop;
                    }
                }
                else
                {
                    if(delta.x > 0)
                    {
                        intersectX = playerRight - tileLeft;
                        intersectY = playerTop - tileBottom;
                    }
                    else
                    {
                        intersectX = playerLeft - tileRight;
                        intersectY = playerTop - tileBottom;
                    }
                }

                if(std::abs(intersectX) < std::abs(intersectY)){
                    vectorSum.x = intersectX;
                }
                else{
                    if(intersectY > 0){
                        setOnGround(true);
                        jumpCount = 0;
                    }
                    vectorSum.y = intersectY;
                }
            }
        }
    }

    //Collision with level borders:

    if(nextPos.left + nextPos.width > (float)currentLevel->getLevelLength() * (float)tileRegistry->tileSize){
        vectorSum.x = -(float)currentLevel->getLevelLength() * (float)tileRegistry->tileSize +  nextPos.left + nextPos.width;
    }
    else if(nextPos.left < 0){
        vectorSum.x = nextPos.left;
    }
    return vectorSum;
}

void Player::enemyCollisions() {
    Game * game = Game::GetInstance();
    ResourceRegistry * resourceRegistry = ResourceRegistry::GetInstance();
    Level * level = game->getCurrentLevel();

    for (auto  enemy : level->entities) {
        if (enemy->getBase() == resourceRegistry->getPresetById(GOOMBA_ENTITY_ID)) {
            if (sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds())) {
                if (sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds())) {
                    if (sprite.getGlobalBounds().left < enemy->sprite.getGlobalBounds().left &&
                        sprite.getGlobalBounds().left + sprite.getGlobalBounds().width <
                        enemy->sprite.getGlobalBounds().left + enemy->sprite.getGlobalBounds().width &&
                        sprite.getGlobalBounds().top <
                        enemy->sprite.getGlobalBounds().top + enemy->sprite.getGlobalBounds().height &&
                        sprite.getGlobalBounds().top + sprite.getGlobalBounds().height >
                        enemy->sprite.getGlobalBounds().top) {

                        setPositionX(enemy->sprite.getGlobalBounds().left - 100.f);
                        setPositionY(sprite.getGlobalBounds().top);
                        enemy->performCollisionStrategy(1);
                        std::cout << "YOU HAVE " << getHP() << " HP LEFT" << std::endl;
                        checkIfPlayerShouldDie();
                    }
                }
                if (sprite.getGlobalBounds().left >
                    enemy->sprite.getGlobalBounds().left - enemy->sprite.getGlobalBounds().width &&
                    sprite.getGlobalBounds().left + sprite.getGlobalBounds().width <
                    enemy->sprite.getGlobalBounds().left + enemy->sprite.getGlobalBounds().width &&
                    sprite.getGlobalBounds().top <
                    enemy->sprite.getGlobalBounds().top + enemy->sprite.getGlobalBounds().height &&
                    sprite.getGlobalBounds().top + sprite.getGlobalBounds().height >
                    enemy->sprite.getGlobalBounds().top) {
                    std::cout << "YOU HAVE " << getHP() << " HP LEFT" << std::endl;
                    setPositionX(enemy->sprite.getGlobalBounds().left + 100.f);
                    setPositionY(sprite.getGlobalBounds().top);
                    enemy->performCollisionStrategy(1);
                    checkIfPlayerShouldDie();
                }
                if (sprite.getGlobalBounds().top < enemy->sprite.getGlobalBounds().top &&
                    sprite.getGlobalBounds().top + sprite.getGlobalBounds().width <
                    enemy->sprite.getGlobalBounds().top + enemy->sprite.getGlobalBounds().height &&
                    sprite.getGlobalBounds().left <
                    enemy->sprite.getGlobalBounds().left + enemy->sprite.getGlobalBounds().width &&
                    sprite.getGlobalBounds().left + sprite.getGlobalBounds().width >
                    enemy->sprite.getGlobalBounds().left) {
                    setPositionX(sprite.getGlobalBounds().left);
                    setPositionY(enemy->sprite.getGlobalBounds().top - sprite.getGlobalBounds().height);
                    std::cout << "GOOMBA HAS BEEN KILLED" << std::endl;
                    enemy->setPosition(10000.f, 10000.f);
                }
            }
        } else if (enemy->getBase() == resourceRegistry->getPresetById(PPLANT_ENTITY_ID)) {
            if (sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds())) {
                playerHealth = 0;
                checkIfPlayerShouldDie();
            }
        } else if (enemy->getBase() == resourceRegistry->getPresetById(COIN_ENTITY_ID)) {
            if (sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds())) {
                std::cout << "GOOD JOB MOVING TO ANOTHER LEVEL!!!" << std::endl;
                enemy->performCollisionStrategy(game->getCurrentLevelId() + 1);
                    enemy->setPosition(10000.f, 10000.f);
                }
            }
        }
    }

#pragma endregion

#pragma region Private_Methods

void Player::setPositionX(float pos_x) {
    this->sprite.setPosition(pos_x, this->sprite.getPosition().y);
}

void Player::setPositionY(float pos_y) {
    this->sprite.setPosition(this->sprite.getPosition().x, pos_y);
}

void Player::changeToStandingTexture() {
    this->sprite.setTextureRect({0, 0, (int)this->standingTexture.getSize().x, (int)this->standingTexture.getSize().y});
    this->sprite.setTexture(this->standingTexture);
}

void Player::changeToJumpingTexture(bool moveDirection) {
    this->sprite.setTextureRect({0, 0, (int)this->jumpingTexture.getSize().x, (int)this->jumpingTexture.getSize().y});
    this->sprite.setTexture(this->jumpingTexture);
    if(moveDirection) sprite.setScale(1,1);
    else sprite.setScale(-1,1);
}

void Player::changeToGif(bool moveDirection) {
    this->sprite.setTextureRect({0, 0, this->gif.getSize().x, this->gif.getSize().y});
    if(moveDirection) sprite.setScale(1,1);
    else sprite.setScale(-1,1);
}

void Player::setOnGround(bool isOnGround) {
    this->onGround = isOnGround;
    if(onGround){
        if(std::abs(this->velocity.x) > 0.2f)
            changeToGif(this->velocity.x > 0.0f);
        else
            changeToStandingTexture();
    }
    else{
        changeToJumpingTexture(goingRight);
    }
}

void Player::move(const float dir_x) {

    this->velocity.x += dir_x * acceleration;

    if (std::abs(this->velocity.x) > this->maxVelocity) {
        this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);
    }
}

void Player::jump() {
    this->velocity.y += -1 * gravity;
    if(std::abs(this->velocity.x) > this->maxVelocity){
        this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);
    }
    if(std::abs(this->velocity.y) > this->maxVelocity){
        this->velocity.y = this->maxVelocity * ((this->velocity.y < 0.f) ? -1.f : 1.f);
    }
}

void Player::receiveDamage(int dmg) {
     playerHealth -= dmg;
}

void Player::setPlayerPosition(sf::Vector2f position) {
    this->sprite.setPosition(position);
}

void Player::setPlayerPosition(int x, int y) {
    this->sprite.setPosition((float)x, (float)y);
}

void Player::checkIfPlayerShouldDie() {
    if(getHP() == 0){
        std::cout << "YOU DIED!" << std::endl;
        setPlayerPosition(spawnPointPos);
        playerHealth += 5;
    }
}

#pragma endregion