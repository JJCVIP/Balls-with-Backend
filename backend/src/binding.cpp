#include <napi.h>
#include <iostream> // Include for debugging
#include "model.h"
#include "ball.h"

static Model model;

void addBall (const Napi::CallbackInfo& info){
    //get Node Enviroment
    Napi::Env env = info.Env();

    //error handling type error
    if (info.Length() < 1 || !info[0].IsObject()){
        Napi::TypeError::New(env, "Expected an Object..... Failed to add Ball").ThrowAsJavaScriptException();
        return;
    }

    //load the JS object as a Napi Object
    Napi::Object obj = info[0].As<Napi::Object>();


    //Check that x,y exist and are numbers
    if(!obj.Get("x").IsNumber() || !obj.Get("y").IsNumber()){
        Napi::TypeError::New(env, "Properties x and y Must be Numbers!").ThrowAsJavaScriptException();
        return;
    }

    //get a position array for the ball constructor
    std::array<double,2> position = {
        obj.Get("x").As<Napi::Number>().DoubleValue(),
        obj.Get("y").As<Napi::Number>().DoubleValue()
    };

    //create a ball
    Ball ball(position);

    //adds the Ball to the model
    model.addBall(ball);
};



// Get Ball Position
Napi::TypedArrayOf<double> getPosition(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Create an instance of Ball and call its testFunction method
    std::array<double,2> inital_pos = {0,0};
    Ball ball(inital_pos);
    std::array<double,2> result = ball.getPosition();

    Napi::TypedArrayOf<double> typedArray = Napi::TypedArrayOf<double>::New(env, result.size());

    for(size_t i=0; i<result.size(); ++i){
        typedArray[i] = result[i];
    }

    // Return the result as a Javascript typedArray
    return typedArray;
}

//GetBallPosititions
Napi::Array getBallPositions(const Napi::CallbackInfo& info){
    //Get the enviroment
    Napi::Env env = info.Env();

    //get the array from model
    std::vector<std::array<double,2>> position = model.getBallPosititions();

    //create Napi Array
    Napi::Array napiArray = Napi::Array::New(env, position.size());
    
    //Populate Napi Array
    for(size_t i = 0; i < position.size(); ++i){
        //create object to stuff in the array
        Napi::Object positionObj = Napi::Object::New(env);
        //set the objects info
        positionObj.Set("x", Napi::Number::New(env, position[i][0]));
        positionObj.Set("y", Napi::Number::New(env, position[i][1]));

        napiArray[i] = positionObj;
    }

    //return the array
    return napiArray;
}

void update(const Napi::CallbackInfo& info){
    // Napi::Env env = info.Env();
    double time_delta = info[0].As<Napi::Number>().DoubleValue();
    model.update(time_delta);
}

// Initialization function for the module
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    //Exports the Model to JS
    exports.Set(Napi::String::New(env, "addBall"), Napi::Function::New(env,addBall));
    
    // Export the getBallsPositon to JavaScript
    exports.Set(Napi::String::New(env, "getBallPositions"), Napi::Function::New(env, getBallPositions));

    exports.Set(Napi::String::New(env, "update"), Napi::Function::New(env,update));
    
    //Just something you always have to do here, returns the exports object
    return exports;
}

// Register the module with Node.js
NODE_API_MODULE(balls, Init)