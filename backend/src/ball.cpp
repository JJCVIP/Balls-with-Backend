#include "ball.h"
#include <algorithm>

Ball::Ball(const std::array<double, 2>& initial_pos): position(initial_pos), velocity({0,0}){
    
}

std::array<double,2> Ball::getPosition() const{
    return position;
}

void Ball::update(const double time_delta, const std::array<short,2>& bounds){
    //Gravity 
    //Reminder positive number is down
    constexpr double g = 9.81;
    const double acceleration_of_gravity = g * (time_delta) * (time_delta);

    velocity[1] += acceleration_of_gravity;
    position[1] += velocity[1] * time_delta;



    //clamp
    position[0] = std::clamp(short(position[0]), short{0}, bounds[0]);
    position[1] = std::clamp(short(position[1]), short{0}, bounds[1]);

    if(position[1] == double(bounds[1])){
        velocity[1] = -1 * velocity[1] * 0.9;
    }

}
