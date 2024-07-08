import * as PIXI from './pixi.mjs'

const app = new PIXI.Application();
await app.init({width : 640, height : 360});

document.body.appendChild(app.canvas);



//add ball event listener
document.getElementById('addBall').addEventListener('click', ()=>{
    //fetch
    fetch('/api/addBall',{
        method: 'POST',
        headers:{
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({x: Math.random()* 1000, y: Math.random() * 1000})
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

function getBallPositions(){
    fetch('/api/getBallPositions')
    .then(response => response.json())
    .then(raw => {
        const data = Array.from(raw);

        const positionDiv = document.getElementById('positions');
        positionDiv.interHTML = '';

        data.forEach((position, index) => {
            // New ball
            if(app.stage.children?.[index] === undefined) {
                const ball = new PIXI.Graphics();
                ball.circle(position.x,position.y, 5);
                ball.fill('red');
                app.stage.addChild(ball);
            }
            // Update existing
            else {
                const ball = app.stage.children?.[index];
                ball.x = position.x;
                ball.y = position.y;
            }
        });
    })
}

globalThis.app = app;

let elapsed = 0;
app.ticker.add((ticker)=>{
    elapsed += ticker.deltaTime;
    
    //update balls
    fetch('/api/update', {
        method: 'POST'
    })
    .then(response => response.ok ? getBallPositions() : console.error("Error Updating"));
})
