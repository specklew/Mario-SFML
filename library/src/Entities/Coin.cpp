#include "Entities/Coin.h"

Coin::Coin(Resource * base) : Entity(base, 0, 0, new StrategyChangeLevel) {

}

Coin::~Coin() {

}

void Coin::updatePhysics() {
    velocity.y += gravity/1000;
    this->sprite.move(velocity);
}

void Coin::updateMovement() {

    srand((unsigned) time(0));
    int randomNumber=1 + (rand() % 6);;
    if(randomNumber%2==0)
    {
        this->move(-1,0);
    } else this->move(1,0);
}

void Coin::move(const float dir_x, const float dir_y) {
    this->velocity.x += dir_x * acceleration;
    if (std::abs(this->velocity.x) > this->maxVelocity) {
        this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);

    }
}