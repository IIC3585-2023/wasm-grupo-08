//var factory = require("./owo.js");
import Module from './owo.js';
const mymod = Module();
//const fs= require('fs');
//import * as fs from 'fs';

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

document.getElementById("submit-button").onclick = () => {
  const taskAmount = document.getElementById("taskAmount").value;
  const clusterAmount = document.getElementById("clusterAmount").value;

  const taskArray = Array.from({length: taskAmount}, () => Math.floor(Math.random() * 100));

    //JS
    let t0 = Date.now();
    const { clusterTasks, totalTime } = assignTasksToClustersH(taskArray, clusterAmount);
    let t1 = Date.now();
    console.log((t1 - t0) / 1000); //devolver esta wea (esta en segundos)
    console.log("Cluster assignments:", clusterTasks); //devolver esta wea
    document.getElementById("JSValue").textContent = (t1-t0)/1000 + " segundos";

    //C++
    const tasksArray = new Uint32Array(taskArray);
    Module()
    .then((instance) => {
    let t0 = Date.now();
    const ptr = instance._malloc(tasksArray.byteLength);
    instance.HEAPU32.set(tasksArray, ptr >> 2);
    const resultCpp = instance.ccall(
      "heuristic",
      "string",
      ["number", "number", "number"],
      [ptr, tasksArray.length, clusterAmount]
    );
    instance._free(ptr);
    console.log(`Result: ${resultCpp}`);
    let t1 = Date.now();
    console.log((t1 - t0) / 1000);
    document.getElementById("wasmValue").textContent = (t1-t0)/1000 + " segundos";
  })
  .catch((e) => {
    console.log(e);
  });

}