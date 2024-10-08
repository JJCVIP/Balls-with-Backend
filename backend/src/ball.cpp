#include "ball.h"
#include <algorithm>

Ball::Ball(const double& mass, const std::array<double, 2>& initial_pos, const std::array<double,2>& initial_velocity)
: mass(mass), position(initial_pos), velocity(initial_velocity){}

std::array<double,3> Ball::getData() const{
    return std::array<double,3>{position[0],position[1],mass};
}

void Ball::update(const double time_delta, const std::array<short,2>& bounds){
    //Gravity 
    //Reminder positive number is down
    constexpr double g = 98.1;
    const double acceleration_of_gravity =  g * (time_delta);

    velocity[1] += acceleration_of_gravity;
    position[1] += velocity[1] * time_delta + ((0.5) * g * time_delta * time_delta);


    //kinematics in the x direction
    position[0] += velocity[0];
    

    //clamp
    position[0] = std::clamp(position[0], 0.0, static_cast<double>(bounds[0]));
    position[1] = std::clamp(position[1], -32000.0, static_cast<double>(bounds[1]));

    if(position[1] == double(bounds[1])){
        velocity[1] *= -1;
    }

    if(position[0] == static_cast<double>(bounds[0]) || position[0] == 0.0){
        velocity[0] *= -0.6;
    }
}


