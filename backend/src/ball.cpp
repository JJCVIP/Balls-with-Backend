#include "ball.h"

Ball::Ball(const std::array<double, 2>& initial_pos): position(initial_pos){
    
}

std::array<double,2> Ball::getPosition() const{
    return position;
}