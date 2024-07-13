#pragma once

#include <vector>
#include <iostream>
#include "ball.h"

class Model{
 private:
    short width;
    short height;
    std::vector<Ball> balls = {};

 public:
    Model(short width , short height);

    void addBall(const Ball& ball);
    void update(const double time_delta);

    std::vector<std::array<double,2>> getBallPosititions() const; 


};