#pragma once

#include <array>

class Ball{
 public:
    double mass;
    std::array<double, 2> position;
    std::array<double, 2> velocity;

    Ball(
     const double& mass,
     const std::array<double, 2>& position,
     const std::array<double, 2>& initial_velocity
     );
   
   
    std::array<double,2> getPosition() const; 

    //ball updating
    void update(const double time_delta, const std::array<short,2>& bounds);
};
