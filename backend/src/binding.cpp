#include <napi.h>
#include <iostream> // Include for debugging
#include "model.h"
#include "ball.h"

//create a model pointer to point to the dynamic constructed model
static std::unique_ptr<Model> model;

void InitModel(const Napi::CallbackInfo& info){
    //get node enviroment
    Napi::Env env = info.Env();

    //Type Error
    if(info.Length() < 2 || (!info[0].IsNumber() || !info[1].IsNumber())){
        std::cout << info[0].IsNumber() << " " << info[1].IsNumber() << std::endl;
        Napi::TypeError::New(env, "Expected 2 short integers ... Failed to create Model").ThrowAsJavaScriptException();
        return;
    }

    const short width = info[0].As<Napi::Number>().Int32Value();
    const short height = info[1].As<Napi::Number>().Int32Value();


    // Debug statement
    std::cout << "Initializing model with width: " << width << ", height: " << height << std::endl;

     model = std::make_unique<Model>(width, height);
    std::cout << "Model initialized successfully." << std::endl;

}

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

    std::array<double,2> iniitial_velocity = {
        obj.Get("initial_vx").As<Napi::Number>().DoubleValue(),
        obj.Get("initial_vy").As<Napi::Number>().DoubleValue()
    };

    auto mass = obj.Get("mass").As<Napi::Number>().DoubleValue();

    //create a ball
    Ball ball(mass, position, iniitial_velocity);

    //adds the Ball to the model
    model->addBall(ball);
};

//GetBallPosititions
Napi::Array getBallData(const Napi::CallbackInfo& info){
    //Get the enviroment
    Napi::Env env = info.Env();

    //get the array from model
    std::vector<std::array<double,3>> data = model->getBallData();

    //create Napi Array
    Napi::Array napiArray = Napi::Array::New(env, data.size());
    
    //Populate Napi Array
    for(size_t i = 0; i < data.size(); ++i){
        //create object to stuff in the array
        Napi::Object ballDataObj = Napi::Object::New(env);
        //set the objects info
        ballDataObj.Set("x", Napi::Number::New(env, data[i][0]));
        ballDataObj.Set("y", Napi::Number::New(env, data[i][1]));
        ballDataObj.Set("mass", Napi::Number::New(env, data[i][2]));

        napiArray[i] = ballDataObj;
    }

    //return the array
    return napiArray;
}

void update(const Napi::CallbackInfo& info){
    // Napi::Env env = info.Env();
    double time_delta = info[0].As<Napi::Number>().DoubleValue();
    model->update(time_delta);
}

// Initialization function for the module
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    //Exports the Model to JS
    exports.Set(Napi::String::New(env, "InitModel"), Napi::Function::New(env,InitModel));

    //Exports Add ball 
    exports.Set(Napi::String::New(env, "addBall"), Napi::Function::New(env,addBall));
    
    // Export the getBallsPositon to JavaScript
    exports.Set(Napi::String::New(env, "getBallData"), Napi::Function::New(env, getBallData));

    // Exports the update func to JS
    exports.Set(Napi::String::New(env, "update"), Napi::Function::New(env,update));
    
    //Just something you always have to do here, returns the exports object
    return exports;
}

// Register the module with Node.js
NODE_API_MODULE(balls, Init)