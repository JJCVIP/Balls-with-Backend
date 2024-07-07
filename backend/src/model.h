#pragma once

#include <vector>
#include <iostream>
#include "ball.h"

class Model{
 public:
    std::vector<Ball> balls;

    void addBall(const Ball& ball);
    void update();

    std::vector<std::array<double,2>> getBallPosititions() const; 


};