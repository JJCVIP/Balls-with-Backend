#include "ball.h"

Ball::Ball(const std::array<double, 2>& initial_pos): position(initial_pos), velocity({0,0}){
    
}

std::array<double,2> Ball::getPosition() const{
    return position;
}

void Ball::update(const double time_delta){

    //Gravity 
    //Reminder positive number is down
    constexpr double g = 9.81;
    const double acceleration_of_gravity = g * (time_delta) * (time_delta);

    velocity[1] += acceleration_of_gravity;
    position[1] += velocity[1] * time_delta;
}
