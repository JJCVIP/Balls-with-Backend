// index.js
const addon = require('./build/Release/balls');

console.log(addon.getBallPositions());
console.log("adding ball...")
addon.addBall({x:1,y:1});

console.log(addon.getBallPositions());

addon.update();

console.log("Likely Success");

