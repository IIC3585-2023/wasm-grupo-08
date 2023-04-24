//var factory = require("./owo.js");
import Module from './owo.js';
const mymod = Module();
//const fs= require('fs');
//git

function assignTasksToClustersH(tasks, numClusters) {
  tasks.sort((a, b) => b - a);

  const completionTimes = new Array(numClusters).fill(0);

  const clusterTasks = new Array(numClusters).fill().map(() => []);
  for (const task of tasks) {
    const minCompletionTimeIndex = completionTimes.indexOf(
      Math.min(...completionTimes)
    );
    clusterTasks[minCompletionTimeIndex].push(task);
    completionTimes[minCompletionTimeIndex] += task;
  }

  const totalTime = Math.max(...completionTimes);
  return { clusterTasks, totalTime };
}

document.getElementById("submit-button").onclick = () => {
  const taskAmount = document.getElementById("taskAmount").value;
  const numClusters = Number(document.getElementById("clusterAmount").value);
  const tasks = Array.from({length: taskAmount}, () => Math.floor(Math.random() * 100));

    //JS
    let t0 = Date.now();
    const clusterTasks = assignTasksToClustersH(tasks, numClusters);
    let t1 = Date.now();
    console.log((t1 - t0) / 1000); //devolver esta wea (esta en segundos)
    console.log("Cluster assignments:", clusterTasks); //devolver esta wea
    document.getElementById("JSValue").textContent = (t1-t0)/1000 + " segundos";

    //C++
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
    let t1 = Date.now();
    console.log(`Result: ${resultCpp}`);
    console.log((t1 - t0) / 1000);
    document.getElementById("wasmValue").textContent = (t1-t0)/1000 + " segundos";
  })
  .catch((e) => {
    console.log(e);
  });

}