#include "model.h"

Model::Model(short width, short height){
    this->bounds[0] = width;
    this->bounds[1] = height;
}


void Model::addBall(const Ball& ball) {
    balls.push_back(ball);
}


std::vector<std::array<double,2>> Model::getBallPosititions() const{
    std::vector<std::array<double,2>> positions;
    positions.reserve(balls.size());
    for(const auto& ball : balls){
        positions.push_back(ball.getPosition());
    }

    return positions;
}

void Model::update(const double time_delta){
   //update all the balls
   for(auto& ball : balls){

        ball.update(time_delta, bounds);
   }
}