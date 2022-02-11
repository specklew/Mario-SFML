#include "Entities/Goomba.h"

Goomba::Goomba(Resource * base) : Entity(base, 1, 4, new StrategyDamagePlayer) {
    srand((unsigned) time(0));
    int randomNumber1=1 + (rand() % 6);
    int randomNumber2=1 + (rand() % 2);
    int randomNumber3=1 + (rand() % 7);
    this->acceleration=acceleration*randomNumber1*randomNumber2*randomNumber3;

}

Goomba::~Goomba() {

}

void Goomba::updatePhysics() {
    velocity.y += gravity/100;
    this->sprite.move(velocity);
}
void Goomba::updateMovement() {

    int randomNumber = 1 + (rand() % 5);;

    if(randomNumber%2==0)
        this->move(-1,0);
    else
        this->move(1,0);

}
void Goomba::move(const float dir_x,const float dir_y) {
    this->velocity.x += dir_x * acceleration;
    if (std::abs(this->velocity.x) > this->maxVelocity) {
        this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);

    }
}