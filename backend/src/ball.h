#pragma once

#include <array>

class Ball{
 public:
    std::array<double, 2> position;
    std::array<double, 2> velocity;

    Ball(const std::array<double, 2>& position);
    std::array<double,2> getPosition() const; 

    //ball updating
    void update(const double time_delta);
};
