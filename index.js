const Module = require("./module.js");
document.getElementById("submit").onclick = () => {
  const tasks = document.getElementById("tasks").value;
  const clusters = document.getElementById("clusters").value;
  const tasksTimes = document.getElementById("tasks-times").value;
  if (clusters !== tasksTimes.length) {
    throw new Error(
      "Clusters value ans task-times size needs to be of the same size."
    );
  }

  const tasksArray = Uint32Array(tasksTimes.split(" ").map((x) => parseInt(x)));
  const t0 = Date.now();
  const result = assignTasksToClustersH(tasks, tasksArray);
  const t1 = Date.now();
  console.log("js heuristic:");
  console.log((t1 - t0) / 1000);
  const ptr = Module._malloc(tasksArray.byteLength);
  Module.HEAPU32.set(tasksArray, ptr >> 2);
};

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

function callCppFunction() {
  var result = Module.ccall(
    "assignTasksToClustersH", // function name
    "number", // return type (int)
    ["number", "number"], // argument types (int, int)
    [arg1, arg2]
  ); // arguments
  document.getElementById("result").textContent = "Result: " + result;
}
