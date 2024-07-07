//add ball event listener
document.getElementById('addBall').addEventListener('click', ()=>{
    //fetch
    fetch('/api/addBall',{
        method: 'POST',
        headers:{
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({x: Math.random()* 100, y: Math.random() * 100})
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
    .then(data => {
        const positionDiv = document.getElementById('positions');
        positionDiv.interHTML = '';

        data.forEach((position, index) =>{
            const div = document.createElement('div');
            div.textContent = `Ball ${index + 1}: x=${position.x}, y=${position.y}`;
            positionDiv.appendChild(div);
        })
    })
}

getBallPositions();