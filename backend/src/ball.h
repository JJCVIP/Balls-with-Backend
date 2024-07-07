#pragma once

#include <array>

class Ball{
 public:
    std::array<double, 2> position;

    Ball(const std::array<double, 2>& position);
    std::array<double,2> getPosition() const; 
};
