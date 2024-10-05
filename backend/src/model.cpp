#include "model.h"

Model::Model(short width, short height){
    this->bounds[0] = width;
    this->bounds[1] = height;
}


void Model::addBall(const Ball& ball) {
    balls.push_back(ball);
}

// There has to be a better way to do this with less memory allocation TODO
std::vector<std::array<double,3>> Model::getBallData() const{
    std::vector<std::array<double,3>> data;
    data.reserve(balls.size());
    for(const auto& ball : balls){
        data.emplace_back(ball.getData());
    }
    return data;
}

void Model::update(const double time_delta){
   //update all the balls
   for(auto& ball : balls){

        ball.update(time_delta, bounds);
   }
}