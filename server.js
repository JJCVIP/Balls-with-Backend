//loads express
const express = require("express");

//load path, A unitility Module that works with file and directory paths
const path = require("path");

//load c++ balls Addon
const balls = require('./backend/build/Release/balls.node');

//creates the express app
const app = express();

//sets the port
const port = 3000;

// shrug, idk will learn later
app.use(express.json());

//serves the static files from the frontend directory
app.use(express.static(path.join(__dirname, 'frontend')));

//API Endpoint to Initilize the Model
app.post('/api/InitModel', (req,res)=>{
    const {width, height} = req.body;
    console.log(`${width}   ${height}`);
    balls.InitModel(width, height);
    //send OK status
    res.sendStatus(200);
});

//API Endpoint (whatever that is) to Add ball
app.post('/api/addBall', (req, res) => {
    const { x , y , initial_vx, initial_vy, mass } = req.body;
    balls.addBall({ x , y, initial_vx, initial_vy, mass});
    //Send OK status
    res.sendStatus(200);
});

//API Endpoint to Get the Ball Data
app.get('/api/getBallData', (req, res) => {
    const ballData = balls.getBallData();
    //sends postion JSON and if successful a 200 status
    res.json(ballData);
})

//API Endpoint to update model
app.post('/api/update', (req,res)=>{
    balls.update(0.1);
    //set OK Status
    res.sendStatus(200);
});

//start the server
app.listen(port, () =>{
    console.log(`Server is running on http://localhost:${port}`)
})