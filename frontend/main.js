import * as PIXI from './pixi.mjs'

const app = new PIXI.Application();

const CANVAS_WIDTH = 1200;
const CANVAS_HIEGHT = 652;
await app.init({width : CANVAS_WIDTH, height : CANVAS_HIEGHT+20});
document.body.appendChild(app.canvas);

//Load Assets
const ballTexture = await PIXI.Assets.load("/assets/Ball.png");

//Set up c++ Model Object
fetch('/api/InitModel',{
    method: 'POST',
    headers:{
        'Content-Type' : 'application/json'
    },
    body: JSON.stringify({width:CANVAS_WIDTH, height:CANVAS_HIEGHT})
})
.then(response => response.ok ? console.log("Model Loaded Sucessfully") : console.error("Error adding Model"));



//add ball event listener
document.getElementById('addBall').addEventListener('click', ()=>{
    //fetch
    fetch('/api/addBall',{
        method: 'POST',
        headers:{
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            x: Math.random()* CANVAS_WIDTH, 
            y: Math.random() *  CANVAS_HIEGHT,
            initial_vx: 10 * (Math.random() - 0.5),
            initial_vy: 10 * (Math.random() - 0.5),
            mass: 10
        })
    })
    .then(response => response.ok ? console.log("ball added") : console.error("Error adding ball"));
});

//update button
document.getElementById('update').addEventListener('click', () =>{
    fetch('/api/update', {
        method: 'POST'
    })
    .then(response => response.ok ? getBallPositions() : console.error("Error Updating"));
});


//balls Sprites
const ballSpritesArray = new Array;

//ball Container
const ballsContainer = new PIXI.Container();
app.stage.addChild(ballsContainer);

function getBallPositions(){
    fetch('/api/getBallPositions')
    .then(response => response.json())
    .then(raw => {
        const data = Array.from(raw);
        console.log(data);

        //ensure that the data array is the same size as the sprite array
        while(data.length > ballSpritesArray.length){

            //const ball = PIXI.Sprite.from(ballTexture);
            ballSpritesArray.push(PIXI.Sprite.from(ballTexture));
            ballSpritesArray.at(-1).width = 10;
            ballSpritesArray.at(-1).height= 10;
            ballsContainer.addChild(ballSpritesArray.at(-1));

        }

        while( data.length < ballSpritesArray.length){
            ballsContainer.stage.removeChild(ballSpritesArray.pop());
        }

        //maps each of the data entries to a cooresponding sprite
        data.forEach((position, index) =>{
            ballSpritesArray[index].x = position.x;
            ballSpritesArray[index].y = position.y;
        });

    })
}


let elapsed = 0;
app.ticker.add((ticker)=>{
    elapsed += ticker.deltaTime;
    
    //update balls
    fetch('/api/update', {
        method: 'POST'
    })
    .then(response => response.ok ? getBallPositions() : console.error("Error Updating"));

})

function update(){
     //update balls
    fetch('/api/update', {
        method: 'POST'
    })
    .then(response => response.ok ? getBallPositions() : console.error("Error Updating"));
}
