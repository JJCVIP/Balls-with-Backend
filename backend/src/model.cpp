#include "model.h"


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

void Model::update(){
    std::cout << "Updating";
}