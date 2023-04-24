import Module from './owo.js';
const mymod = Module();
import * as fs from 'fs';

function assignTasksToClustersH(tasks, numClusters) {
  // Step 1: sort tasks in descending order of completion time
  tasks.sort((a, b) => b - a);

  // Step 2: initialize array of completion times for each cluster
  const completionTimes = new Array(numClusters).fill(0);

  // Step 3: assign tasks to clusters
  const clusterTasks = new Array(numClusters).fill().map(() => []);
  for (const task of tasks) {
    const minCompletionTimeIndex = completionTimes.indexOf(
      Math.min(...completionTimes)
    );
    clusterTasks[minCompletionTimeIndex].push(task);
    completionTimes[minCompletionTimeIndex] += task;
  }

  // Step 4: return results
  const totalTime = Math.max(...completionTimes);
  return { clusterTasks, totalTime };
}

//const tasks = [30, 50, 10, 20, 90,30, 50, 10, 20, 90,30, 50, 10, 20, 90,30, 50, 10, 20, 90,30, 50, 10, 20, 90];
//const numClusters = 2;
/*
document.getElementById("submit-button").onclick = () => {
  const inputFile = document.getElementById("inputFile").value;
  /*
    if (inputFile !== tasksTimes.length) {
    throw new Error(
      "Invalid Input File"
    );
  
    //Reading input file
    const content = fs.readFileSync("inputFile", {encoding:'utf8', flag:'r'});
    const contentAsList = content.split(" ");
    const numClusters = Number(contentAsList[1]); //workers
    const tasks = contentAsList.slice(2).map(Number);
    //JS
    let t0 = Date.now();
    const { clusterTasks, totalTime } = assignTasksToClustersH(tasks, numClusters);
    let t1 = Date.now();
    console.log((t1 - t0) / 1000); //devolver esta wea (esta en segundos)
    console.log("Cluster assignments:", clusterTasks); //devolver esta wea
    //C++
    const tasksArray = new Uint32Array(tasks);
    factory()
    .then((instance) => {
    let t0 = Date.now();
    const ptr = instance._malloc(tasksArray.byteLength);
    instance.HEAPU32.set(tasksArray, ptr >> 2);
    const resultCpp = instance.ccall(
      "heuristic",
      "string",
      ["number", "number", "number"],
      [ptr, tasksArray.length, 2]
    );
    instance._free(ptr);
    console.log(`Result: ${resultCpp}`);
    let t1 = Date.now();
    console.log((t1 - t0) / 1000);
  })
  .catch((e) => {
    console.log(e);
  });

}
*/


const content = fs.readFileSync("input.txt", {encoding:'utf8', flag:'r'});
const contentAsList = content.split(" ");
const numClusters = Number(contentAsList[1]); //workers
const tasks = contentAsList.slice(2).map(Number);

// Assign tasks to clusters
let t0 = Date.now();
const { clusterTasks, totalTime } = assignTasksToClustersH(tasks, numClusters);
let t1 = Date.now();
console.log((t1 - t0) / 1000);
// Print the result
console.log("Cluster assignments:", clusterTasks);
//console.log("Total time:", totalTime);


const tasksArray = new Uint32Array(tasks);
Module()
  .then((instance) => {
    let t0 = Date.now();
    const ptr = instance._malloc(tasksArray.byteLength);
    instance.HEAPU32.set(tasksArray, ptr >> 2);
    const resultCpp = instance.ccall(
      "heuristic",
      "string",
      ["number", "number", "number"],
      [ptr, tasksArray.length, numClusters]
    );
    instance._free(ptr);
    console.log(`Result: ${resultCpp}`);
    let t1 = Date.now();
    console.log((t1 - t0) / 1000);
  })
  .catch((e) => {
    console.log(e);
  });

//   const ptr = Module._malloc(tasksArray.byteLength);
//   Module.HEAPU32.set(tasksArray, ptr >> 2);
//   const resultCpp = Module.ccall(
//     "heuristic",
//     "string",
//     ["number", "number", "number"],
//     [ptr, 5, 2]
//   );
//   Module._free(ptr);
//   console.log(`Result: ${resultCpp}`);