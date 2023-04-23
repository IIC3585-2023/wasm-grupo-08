var factory = require('./api.js');
const fs = require('fs');
let a =1;
let b =2;
const content = fs.readFileSync("input.txt", {encoding:'utf8', flag:'r'});
const contentAsList = content.split(" ");
const n = Number(contentAsList[0]); //tareas
const m = Number(contentAsList[1]); //workers
const jobTimes = contentAsList.slice(2).map(Number);
factory().then((instance) => {
  //instance._sayHi(); // direct calling works
  //instance.ccall("sayHi"); // using ccall etc. also work
  //console.log(instance._encontrarAsignacionOptima(n,jobTimes,m));
  console.log(instance._Addx(2,1)); // values can be returned, etc.
  //console.log(instance._heuristic([2,2],2,1)); // values can be returned, etc.
});
/*
var result = Module.ccall('_Addx', // name of C function
  'number', // return type
  ['number', 'number'], // argument types
  [10, 20]); // arguments 
  console.log(result);
  */